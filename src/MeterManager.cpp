/*
 * MeterManager.cpp
 *
 *  Created on: Feb 7, 2024
 *      Author: olavt
 */

#include "MeterManager.h"
#include "AidonElectricityMeter.h"
#include "sl_sleeptimer.h"
#include <functional>

#include <app/server/Server.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/clusters/electrical-energy-measurement-server/electrical-energy-measurement-server.h>

using namespace std::chrono;
using namespace chip;
using namespace chip::app;
using namespace chip::app::DataModel;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::ElectricalEnergyMeasurement;
using namespace chip::app::Clusters::ElectricalEnergyMeasurement::Structs;

#define ELECTRICAL_SENSOR_ENDPOINT 1

void MeterManager::Init()
{
  _electricalPowerMeasurementDelegate = new ElectricalPowerMeasurementDelegate();

  _electricalPowerMeasurementInstance = new ElectricalPowerMeasurementInstance(
      EndpointId(ELECTRICAL_SENSOR_ENDPOINT),
      *_electricalPowerMeasurementDelegate,
      BitMask<ElectricalPowerMeasurement::Feature, uint32_t>(
          ElectricalPowerMeasurement::Feature::kDirectCurrent,
          ElectricalPowerMeasurement::Feature::kAlternatingCurrent
          ),
      BitMask<ElectricalPowerMeasurement::OptionalAttributes, uint32_t>(0));

  _electricalPowerMeasurementInstance->Init();

  char instanceName[] = "mikroe";
  std::unique_ptr<SerialPort> serialPort = std::make_unique<SerialPort>(instanceName);
  serialPort->SetReadBlockingMode(false);

  _electricityMeter = std::make_unique<AidonElectricityMeter>(std::move(serialPort));
  //_electricityMeter = std::make_unique<AidonElectricityMeter>(nullptr);

  _electricityMeter->OnActivePowerUpdated = std::bind(&MeterManager::OnActivePowerUpdated, this);
  _electricityMeter->OnCumulativeEnergyUpdated = std::bind(&MeterManager::OnCumulativeEnergyUpdated, this);
}

void MeterManager::ReadMeters()
{
  SILABS_LOG("MeterManager::ReadMeters: Start");

  //auto start = sl_sleeptimer_get_tick_count64();
  //auto start = steady_clock::now();
  auto start = chip::System::SystemClock().GetMonotonicMilliseconds64().count();

  if (!_electricityMeter) {
      SILABS_LOG("MeterManager::ReadMeters: _electricityMeter is nullptr.");
      return;
  }

  _electricityMeter->ReadFromHanPort();

  //auto stop = sl_sleeptimer_get_tick_count64();
  //auto stop = steady_clock::now();
  auto stop = chip::System::SystemClock().GetMonotonicMilliseconds64().count();
  SILABS_LOG("MeterManager::ReadMeters: Stop");

  //uint64_t ms;
  //sl_sleeptimer_tick64_to_ms(stop - start, &ms);
  //auto ms = duration_cast<milliseconds>(stop - start).count();
  auto ms = stop - start;

  SILABS_LOG("MeterManager::ReadMeters: Execution completed in %d ms.", (uint32_t)ms);
}

void MeterManager::OnActivePowerUpdated()
{
  double watts = _electricityMeter->ActivePower();
  //watts = rand() % 5000 + 200;

  int64_t aActivePower_mW = watts * 1000;
  _electricalPowerMeasurementDelegate->SetActivePower(MakeNullable(aActivePower_mW));
}

void MeterManager::OnCumulativeEnergyUpdated()
{
  double kwh = _electricityMeter-> CumulativeImportEnergy();
  //kwh = rand() % 50000 + 200;
  int64_t aCumulativeEnergyImported = kwh * 1000 * 1000;
  int64_t aCumulativeEnergyExported = 0;

  SendCumulativeEnergyReading(ELECTRICAL_SENSOR_ENDPOINT, aCumulativeEnergyImported, aCumulativeEnergyExported);
}

CHIP_ERROR MeterManager::SendCumulativeEnergyReading(EndpointId aEndpointId, int64_t aCumulativeEnergyImported,
                                                         int64_t aCumulativeEnergyExported)
{
    MeasurementData * data = MeasurementDataForEndpoint(aEndpointId);
    VerifyOrReturnError(data != nullptr, CHIP_ERROR_UNINITIALIZED);

    EnergyMeasurementStruct::Type energyImported;
    EnergyMeasurementStruct::Type energyExported;

    /** IMPORT */
    // Copy last endTimestamp into new startTimestamp if it exists
    energyImported.startTimestamp.ClearValue();
    energyImported.startSystime.ClearValue();
    if (data->cumulativeImported.HasValue())
    {
        energyImported.startTimestamp = data->cumulativeImported.Value().endTimestamp;
        energyImported.startSystime   = data->cumulativeImported.Value().endSystime;
    }

    energyImported.energy = aCumulativeEnergyImported;

    /** EXPORT */
    // Copy last endTimestamp into new startTimestamp if it exists
    energyExported.startTimestamp.ClearValue();
    energyExported.startSystime.ClearValue();
    if (data->cumulativeExported.HasValue())
    {
        energyExported.startTimestamp = data->cumulativeExported.Value().endTimestamp;
        energyExported.startSystime   = data->cumulativeExported.Value().endSystime;
    }

    energyExported.energy = aCumulativeEnergyExported;

    // Get current timestamp
    uint32_t currentTimestamp;
    CHIP_ERROR err = GetEpochTS(currentTimestamp);
    if (err == CHIP_NO_ERROR)
    {
        // use EpochTS
        energyImported.endTimestamp.SetValue(currentTimestamp);
        energyExported.endTimestamp.SetValue(currentTimestamp);
    }
    else
    {
        ChipLogError(AppServer, "GetEpochTS returned error getting timestamp %" CHIP_ERROR_FORMAT, err.Format());

        // use systemTime as a fallback
        System::Clock::Milliseconds64 system_time_ms =
            std::chrono::duration_cast<System::Clock::Milliseconds64>(chip::Server::GetInstance().TimeSinceInit());
        uint64_t nowMS = static_cast<uint64_t>(system_time_ms.count());

        energyImported.endSystime.SetValue(nowMS);
        energyExported.endSystime.SetValue(nowMS);
    }

    // call the SDK to update attributes and generate an event
    if (!NotifyCumulativeEnergyMeasured(aEndpointId, MakeOptional(energyImported), MakeOptional(energyExported)))
    {
        ChipLogError(AppServer, "Failed to notify Cumulative Energy reading.");
        return CHIP_ERROR_INTERNAL;
    }

    return CHIP_NO_ERROR;
}

/**
 * @brief   Helper function to get current timestamp in Epoch format
 *
 * @param   chipEpoch reference to hold return timestamp
 */
CHIP_ERROR MeterManager::GetEpochTS(uint32_t & chipEpoch)
{
    chipEpoch = 0;

    System::Clock::Milliseconds64 cTMs;
    CHIP_ERROR err = System::SystemClock().GetClock_RealTimeMS(cTMs);

    /* If the GetClock_RealTimeMS returns CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE, then
     * This platform cannot ever report real time !
     * This should not be certifiable since getting time is a Mandatory
     * feature of EVSE Cluster
     */
    if (err == CHIP_ERROR_UNSUPPORTED_CHIP_FEATURE)
    {
        ChipLogError(Zcl, "Platform does not support GetClock_RealTimeMS. Check EVSE certification requirements!");
        return err;
    }

    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(Zcl, "EVSE: Unable to get current time - err:%" CHIP_ERROR_FORMAT, err.Format());
        return err;
    }

    auto unixEpoch = std::chrono::duration_cast<System::Clock::Seconds32>(cTMs).count();
    if (!UnixEpochToChipEpochTime(unixEpoch, chipEpoch))
    {
        ChipLogError(Zcl, "EVSE: unable to convert Unix Epoch time to Matter Epoch Time");
        return err;
    }

    return CHIP_NO_ERROR;
}

static std::unique_ptr<ElectricalEnergyMeasurementAttrAccess> gAttrAccess;

void emberAfElectricalEnergyMeasurementClusterInitCallback(chip::EndpointId endpointId)
{
  VerifyOrDie(endpointId == ELECTRICAL_SENSOR_ENDPOINT); // this cluster is only enabled for endpoint 1.
  VerifyOrDie(!gAttrAccess);

  gAttrAccess = std::make_unique<ElectricalEnergyMeasurementAttrAccess>(
      BitMask<ElectricalEnergyMeasurement::Feature, uint32_t>(
          ElectricalEnergyMeasurement::Feature::kImportedEnergy,
          ElectricalEnergyMeasurement::Feature::kExportedEnergy,
          ElectricalEnergyMeasurement::Feature::kCumulativeEnergy,
          ElectricalEnergyMeasurement::Feature::kPeriodicEnergy),
      BitMask<ElectricalEnergyMeasurement::OptionalAttributes, uint32_t>(
          ElectricalEnergyMeasurement::OptionalAttributes::kOptionalAttributeCumulativeEnergyReset));

  // Create an accuracy entry which is between +/-0.5 and +/- 5% across the range of all possible energy readings
  ElectricalEnergyMeasurement::Structs::MeasurementAccuracyRangeStruct::Type energyAccuracyRanges[] = {
      { .rangeMin   = 0,
        .rangeMax   = 999'999'999'999, // mWh
        .percentMax = MakeOptional(static_cast<chip::Percent100ths>(500)),
        .percentMin = MakeOptional(static_cast<chip::Percent100ths>(50)) }
  };

  ElectricalEnergyMeasurement::Structs::MeasurementAccuracyStruct::Type accuracy = {
      .measurementType  = MeasurementTypeEnum::kElectricalEnergy,
      .measured         = true,
      .minMeasuredValue = 0,
      .maxMeasuredValue = 999'999'999'999, // mWh
      .accuracyRanges =
          DataModel::List<const ElectricalEnergyMeasurement::Structs::MeasurementAccuracyRangeStruct::Type>(energyAccuracyRanges)
  };

  if (gAttrAccess)
  {
      gAttrAccess->Init();

      SetMeasurementAccuracy(endpointId, accuracy);
  }
}


