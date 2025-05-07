/*
 * MeterManager.h
 *
 *  Created on: Feb 7, 2024
 *      Author: olavt
 */

#pragma once

#include <memory>

#include "SerialPort.h"
#include "ElectricityMeter.h"
#include "ElectricalPowerMeasurementDelegate.h"

using namespace chip::app::Clusters::ElectricalPowerMeasurement;

class MeterManager
{

public:

  void Init();

  void ReadMeters();

private:

  std::unique_ptr<ElectricityMeter> _electricityMeter;
  ElectricalPowerMeasurementDelegate* _electricalPowerMeasurementDelegate;
  ElectricalPowerMeasurementInstance* _electricalPowerMeasurementInstance;

  void OnActivePowerUpdated();

  void OnCumulativeEnergyUpdated();

  CHIP_ERROR SendCumulativeEnergyReading(chip::EndpointId aEndpointId, int64_t aCumulativeEnergyImported,
                                         int64_t aCumulativeEnergyExported);

  CHIP_ERROR GetEpochTS(uint32_t & chipEpoch);

};
