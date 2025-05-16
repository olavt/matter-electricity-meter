/*
 * AidonElectricityMeter.cpp
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#include "AidonElectricityMeter.h"
#include "CosemInteger8.h"
#include "CosemUnsigned16.h"
#include "CosemUnsigned32.h"
#include "CosemVisibleString.h"
#include "silabs_utils.h"
#include <cmath>
#include <iomanip>
#include <sstream>

AidonElectricityMeter::AidonElectricityMeter(std::unique_ptr<SerialPort> serialPort) : ElectricityMeter(std::make_unique<AidonHanReader>(std::move(serialPort)))
{
}

void AidonElectricityMeter::ReadFromHanPort()
{
  if (!_hanReader) {
      SILABS_LOG("AidonElectricityMeter::ReadFromHanPort: _hanReader is nullptr.");
      return;
  }

  std::unique_ptr<CosemArray> meterData = _hanReader->ReadMeterData();
  if (meterData == nullptr)
    return;

  ProcessMeterData(meterData);

  OnMeterDataProcessingCompleted();
}

void AidonElectricityMeter::ProcessOBISListVersionIdentifier(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;

  // List #: 2, 3
  CosemVisibleString* versionIdentifier = dynamic_cast<CosemVisibleString*>((*cosemStructure)[1]);
  if (versionIdentifier == nullptr)
      return;

  SILABS_LOG("OBIS List version identifier: %s", versionIdentifier->ToString().c_str());
}

void AidonElectricityMeter::ProcessMeterId(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;

  // List #: 2, 3
  CosemVisibleString* meterId = dynamic_cast<CosemVisibleString*>((*cosemStructure)[1]);
  if (meterId)
      UpdateMeterId(meterId->ToString());
}

void AidonElectricityMeter::ProcessMeterType(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;

  // List #: 2, 3
  CosemVisibleString* meterType = dynamic_cast<CosemVisibleString*>((*cosemStructure)[1]);
  if (meterType)
      UpdateMeterType(meterType->ToString());
}

void AidonElectricityMeter::ProcessActivePowerPlus(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;

  // List #: 1
  // Received every 2.5 seconds
  CosemUnsigned32* value = dynamic_cast<CosemUnsigned32*>((*cosemStructure)[1]);
  if (!value) {
      SILABS_LOG("AidonElectricityMeter::ProcessActivePowerPlus: value is nullptr.");
      return;
  }

  CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  if (!scaleUnitStructure) {
      SILABS_LOG("AidonElectricityMeter::ProcessActivePowerPlus: scaleUnitStructure is nullptr.");
      return;
  }

  if (value && scaleUnitStructure) {
      CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
      if (!scale) {
          SILABS_LOG("AidonElectricityMeter::ProcessActivePowerPlus: scale is nullptr.");
          return;
      }

      double watts = value->Value() * pow(10, scale->Value());
      UpdateActivePowerPlus(watts);
  }
}

void AidonElectricityMeter::ProcessActivePowerMinus(std::unique_ptr<CosemStructure>& cosemStructure)
{
  // List #: 2, 3
  //CosemUnsigned32* value = dynamic_cast<CosemUnsigned32*>((*cosemStructure)[1]);
  //CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  //CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
  //double watts = value->Value() * pow(10, scale->Value());
}

void AidonElectricityMeter::ProcessReactivePowerPlus(std::unique_ptr<CosemStructure>& cosemStructure)
{
}

void AidonElectricityMeter::ProcessReactivePowerMinus(std::unique_ptr<CosemStructure>& cosemStructure)
{
}

void AidonElectricityMeter::ProcessCurrentPhaseL1(std::unique_ptr<CosemStructure>& cosemStructure)
{
}

void AidonElectricityMeter::ProcessCurrentPhaseL2(std::unique_ptr<CosemStructure>& cosemStructure)
{
}

void AidonElectricityMeter::ProcessCurrentPhaseL3(std::unique_ptr<CosemStructure>& cosemStructure)
{
}

void AidonElectricityMeter::ProcessInstantaneousVoltageL1(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;

  // List #: 2, 3
  CosemUnsigned16* value = dynamic_cast<CosemUnsigned16*>((*cosemStructure)[1]);
  CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  if (value && scaleUnitStructure) {
      CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
      if (scale) {
          double volt = value->Value() * pow(10, scale->Value());
          UpdateInstantaneousVoltageL1(volt);
      }
  }
}

void AidonElectricityMeter::ProcessInstantaneousVoltageL2(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;

  // List #: 2, 3
  CosemUnsigned16* value = dynamic_cast<CosemUnsigned16*>((*cosemStructure)[1]);
  CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  if (value && scaleUnitStructure) {
      CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
      if (scale) {
          double volt = value->Value() * pow(10, scale->Value());
          UpdateInstantaneousVoltageL2(volt);
      }
  }
}

void AidonElectricityMeter::ProcessInstantaneousVoltageL3(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;

  // List #: 2, 3
  CosemUnsigned16* value = dynamic_cast<CosemUnsigned16*>((*cosemStructure)[1]);
  CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  if (value && scaleUnitStructure) {
      CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
      if (scale) {
          double volt = value->Value() * pow(10, scale->Value());
          UpdateInstantaneousVoltageL3(volt);
      }
  }
}

void AidonElectricityMeter::ProcessMeterDateTime(std::unique_ptr<CosemStructure>& cosemStructure)
{
}

void AidonElectricityMeter::ProcessCumulativeHourlyActiveImportEnergy(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;

  // List #: 3

  _electricityEstimator.TopOfHourReset();

  _electricityEstimator.TopOfHourReset();

  CosemUnsigned32* value = dynamic_cast<CosemUnsigned32*>((*cosemStructure)[1]);
  CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  if (value && scaleUnitStructure) {
      CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
      if (scale) {
          double kwh = value->Value() * pow(10, scale->Value()) / 1000.0;
          UpdateCumulativeActiveImportEnergy(kwh);
      }
  }
}

void AidonElectricityMeter::ProcessCumulativeHourlyActiveExportEnergy(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;
}

void AidonElectricityMeter::ProcessCumulativeHourlyReactiveImportEnergy(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;
}

void AidonElectricityMeter::ProcessCumulativeHourlyReactiveExportEnergy(std::unique_ptr<CosemStructure>& cosemStructure)
{
  if (!cosemStructure)
      return;
}

void AidonElectricityMeter::ProcessRow(std::unique_ptr<CosemStructure>& cosemStructure)
{
    if (!cosemStructure || cosemStructure->size() == 0)
        return;

    // The first child of the CosemStructure should be a CosemOctetString containing an OBIS code
    CosemObject* cosemObject = (*cosemStructure.get())[0];
    CosemOctetString* octetString = dynamic_cast<CosemOctetString*>(cosemObject);
    if (!octetString)
        return;

    std::string obisCode = octetString->ToObisCodeString();
    SILABS_LOG("AidonElectricityMeter::ProcessRow: %s", obisCode.c_str());

    if (obisCode == "1-1:0.2.129.255")      // OBIS List version identifier
        ProcessOBISListVersionIdentifier(cosemStructure);
    else if (obisCode == "0-0:96.1.0.255")  // Meter -ID (GIAI GS1 -16 digit)
        ProcessMeterId(cosemStructure);
    else if (obisCode == "0-0:96.1.7.255")  // Meter type
        ProcessMeterType(cosemStructure);
    else if (obisCode == "1-0:1.7.0.255")   // Active power+ (Q1+Q4)
        ProcessActivePowerPlus(cosemStructure);
    else if (obisCode == "1-0:2.7.0.255")   // Active power - (Q2+Q3)
        ProcessActivePowerMinus(cosemStructure);
    else if (obisCode == "1-0:3.7.0.255")   // Reactive power + (Q1+Q2)
        ProcessReactivePowerPlus(cosemStructure);
    else if (obisCode == "1-0:4.7.0.255")   // Reactive power - (Q3+Q4)
        ProcessReactivePowerMinus(cosemStructure);
    else if (obisCode == "1-0:31.7.0.255")  // IL1 Current phase L1
        ProcessCurrentPhaseL1(cosemStructure);
    else if (obisCode == "1-0:51.7.0.255")  // IL2 Current phase L2
        ProcessCurrentPhaseL2(cosemStructure);
    else if (obisCode == "1-0:71.7.0.255")  // IL3 Current phase L3
        ProcessCurrentPhaseL3(cosemStructure);
    else if (obisCode == "1-0:32.7.0.255")  // UL1 Phase voltage
        ProcessInstantaneousVoltageL1(cosemStructure);
    else if (obisCode == "1-0:52.7.0.255")  // UL2 Phase voltage
        ProcessInstantaneousVoltageL2(cosemStructure);
    else if (obisCode == "1-0:72.7.0.255")  // UL3 Phase voltage
        ProcessInstantaneousVoltageL3(cosemStructure);
    else if (obisCode == "0-0:1.0.0.255")   // Clock and date in meter
        ProcessMeterDateTime(cosemStructure);
    else if (obisCode == "1-0:1.8.0.255")   // Cumulative hourly active import energy
        ProcessCumulativeHourlyActiveImportEnergy(cosemStructure);
    else if (obisCode == "1-0:2.8.0.255")   // Cumulative hourly active export energy
        ProcessCumulativeHourlyActiveExportEnergy(cosemStructure);
    else if (obisCode == "1-0:3.8.0.255")   // Cumulative hourly reactive import energy
        ProcessCumulativeHourlyReactiveImportEnergy(cosemStructure);
    else if (obisCode == "1-0:4.8.0.255")   // Cumulative hourly reactive export energy
        ProcessCumulativeHourlyReactiveExportEnergy(cosemStructure);
}

void AidonElectricityMeter::ProcessMeterData(std::unique_ptr<CosemArray>& cosemArray)
{
  if (!cosemArray)
      return;

  for (int i=0; i < cosemArray->size(); i++)
  {
      CosemObject* cosemObject = (*cosemArray.get())[i];

      // Each row in the array is expected to contain a CosemStructure object, process it
      auto cosemStructure = std::unique_ptr<CosemStructure>(dynamic_cast<CosemStructure*>(cosemObject));
      if (cosemStructure != nullptr)
        ProcessRow(cosemStructure);
  }
}


