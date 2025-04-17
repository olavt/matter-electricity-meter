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

AidonElectricityMeter::AidonElectricityMeter(SerialPort* serialPort) : ElectricityMeter(CreateHanReader(serialPort))
{
}

AidonHanReader* AidonElectricityMeter::CreateHanReader(SerialPort* serialPort)
{
  return new AidonHanReader(serialPort);
}

void AidonElectricityMeter::ReadFromHanPort()
{

  CosemArray* meterData = _hanReader->ReadMeterData();
  if (meterData == NULL)
    return;

  ProcessMeterData(meterData);

  delete meterData;

  OnMeterDataProcessingCompleted();
}

void AidonElectricityMeter::ProcessOBISListVersionIdentifier(CosemStructure* cosemStructure)
{
  // List #: 2, 3
  CosemVisibleString* versionIdentifier = dynamic_cast<CosemVisibleString*>((*cosemStructure)[1]);
  if (versionIdentifier == NULL)
    return;

  SILABS_LOG("OBIS List version identifier: %s", versionIdentifier->ToString().c_str());
}

void AidonElectricityMeter::ProcessMeterId(CosemStructure* cosemStructure)
{
  // List #: 2, 3
  CosemVisibleString* meterId = dynamic_cast<CosemVisibleString*>((*cosemStructure)[1]);
  UpdateMeterId(meterId->ToString());
}

void AidonElectricityMeter::ProcessMeterType(CosemStructure* cosemStructure)
{
  // List #: 2, 3
  CosemVisibleString* meterType = dynamic_cast<CosemVisibleString*>((*cosemStructure)[1]);
  UpdateMeterType(meterType->ToString());
}

void AidonElectricityMeter::ProcessActivePowerPlus(CosemStructure* cosemStructure)
{
  // List #: 1
  // Received every 2.5 seconds
  CosemUnsigned32* value = dynamic_cast<CosemUnsigned32*>((*cosemStructure)[1]);
  CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
  double watts = value->Value() * pow(10, scale->Value());
  UpdateActivePowerPlus(watts);
}

void AidonElectricityMeter::ProcessActivePowerMinus(CosemStructure* cosemStructure)
{
  // List #: 2, 3
  //CosemUnsigned32* value = dynamic_cast<CosemUnsigned32*>((*cosemStructure)[1]);
  //CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  //CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
  //double watts = value->Value() * pow(10, scale->Value());
}

void AidonElectricityMeter::ProcessReactivePowerPlus(CosemStructure* cosemStructure)
{
}

void AidonElectricityMeter::ProcessReactivePowerMinus(CosemStructure* cosemStructure)
{
}

void AidonElectricityMeter::ProcessCurrentPhaseL1(CosemStructure* cosemStructure)
{
}

void AidonElectricityMeter::ProcessCurrentPhaseL2(CosemStructure* cosemStructure)
{
}

void AidonElectricityMeter::ProcessCurrentPhaseL3(CosemStructure* cosemStructure)
{
}

void AidonElectricityMeter::ProcessInstantaneousVoltageL1(CosemStructure* cosemStructure)
{
  // List #: 2, 3
  CosemUnsigned16* value = dynamic_cast<CosemUnsigned16*>((*cosemStructure)[1]);
  CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
  double volt = value->Value() * pow(10, scale->Value());
  UpdateInstantaneousVoltageL1(volt);
}

void AidonElectricityMeter::ProcessInstantaneousVoltageL2(CosemStructure* cosemStructure)
{
  // List #: 2, 3
  CosemUnsigned16* value = dynamic_cast<CosemUnsigned16*>((*cosemStructure)[1]);
  CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
  double volt = value->Value() * pow(10, scale->Value());
  UpdateInstantaneousVoltageL2(volt);
}

void AidonElectricityMeter::ProcessInstantaneousVoltageL3(CosemStructure* cosemStructure)
{
  // List #: 2, 3
  CosemUnsigned16* value = dynamic_cast<CosemUnsigned16*>((*cosemStructure)[1]);
  CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
  double volt = value->Value() * pow(10, scale->Value());
  UpdateInstantaneousVoltageL3(volt);
}

void AidonElectricityMeter::ProcessMeterDateTime(CosemStructure* cosemStructure)
{
}

void AidonElectricityMeter::ProcessCumulativeHourlyActiveImportEnergy(CosemStructure* cosemStructure)
{
  // List #: 3

  _electricityEstimator.TopOfHourReset();

  CosemUnsigned32* value = dynamic_cast<CosemUnsigned32*>((*cosemStructure)[1]);
  CosemStructure* scaleUnitStructure = dynamic_cast<CosemStructure*>((*cosemStructure)[2]);
  CosemInteger8* scale = dynamic_cast<CosemInteger8*>((*scaleUnitStructure)[0]);
  double kwh = value->Value() * pow(10, scale->Value()) / 1000.0;
  UpdateCumulativeActiveImportEnergy(kwh);
}

void AidonElectricityMeter::ProcessCumulativeHourlyActiveExportEnergy(CosemStructure* cosemStructure)
{
}

void AidonElectricityMeter::ProcessCumulativeHourlyReactiveImportEnergy(CosemStructure* cosemStructure)
{
}

void AidonElectricityMeter::ProcessCumulativeHourlyReactiveExportEnergy(CosemStructure* cosemStructure)
{
}

void AidonElectricityMeter::ProcessRow(CosemStructure* cosemStructure)
{
  if (cosemStructure->size() == 0)
    return;

  // The first child of the CosemStructure should be a CosemOctetString containing an OBIS code
  CosemObject* cosemObject = (*cosemStructure)[0];
  CosemOctetString* octetString = dynamic_cast<CosemOctetString*>(cosemObject);
  std::string obisCode = octetString->ToObisCodeString();
  //SILABS_LOG("%s", obisCode.c_str());

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
  else if (obisCode == "1-0:3.7.0.255")   // Reactive power + ( Q1+Q2)
      ProcessReactivePowerPlus(cosemStructure);
  else if (obisCode == "1-0:4.7.0.255")   // Reactive power - ( Q3+Q4)
      ProcessReactivePowerMinus(cosemStructure);
  else if (obisCode == "1-0:31.7.0.255")  // IL1 Current phase L1
      ProcessCurrentPhaseL1(cosemStructure);
  else if (obisCode == "1-0:51.7.0.255")  // IL2 Current phase L2, missing from 3-phase 3W meters and 1-phase meters
      ProcessCurrentPhaseL2(cosemStructure);
  else if (obisCode == "1-0:71.7.0.255")  // IL3 Current phase L3, missing from 1-phase meter
      ProcessCurrentPhaseL3(cosemStructure);
  else if (obisCode == "1-0:32.7.0.255")  // UL1 Phase voltage 4W meter, line voltage 3W meter
      ProcessInstantaneousVoltageL1(cosemStructure);
  else if (obisCode == "1-0:52.7.0.255")  // UL2 Phase voltage 4W meter, line voltage 3W meter
      ProcessInstantaneousVoltageL2(cosemStructure);
  else if (obisCode == "1-0:72.7.0.255")  // UL3 Phase voltage 4W meter, line voltage 3W meter
      ProcessInstantaneousVoltageL3(cosemStructure);
  else if (obisCode == "0-0:1.0.0.255")   // Clock and date in meter
      ProcessMeterDateTime(cosemStructure);
  else if (obisCode == "1-0:1.8.0.255")   // Cumulative hourly active import energy (A+) (Q1+Q4)
      ProcessCumulativeHourlyActiveImportEnergy(cosemStructure);
  else if (obisCode == "1-0:2.8.0.255")   // Cumulative hourly active export energy (A-) (Q2+Q3)
      ProcessCumulativeHourlyActiveExportEnergy(cosemStructure);
  else if (obisCode == "1-0:3.8.0.255")   // Cumulative hourly reactive import energy (R+) (Q1+Q2)
      ProcessCumulativeHourlyReactiveImportEnergy(cosemStructure);
  else if (obisCode == "1-0:4.8.0.255")   // Cumulative hourly reactive export energy (R-) (Q3+Q4)
      ProcessCumulativeHourlyReactiveExportEnergy(cosemStructure);
}

void AidonElectricityMeter::ProcessMeterData(CosemArray* cosemArray)
{
  if (cosemArray == 0)
    return;

  for (int i=0; i < cosemArray->size(); i++)
  {
      CosemObject* cosemObject = (*cosemArray)[i];
      CosemStructure* cosemStructure = dynamic_cast<CosemStructure*>(cosemObject);
      if (cosemStructure != 0)
        ProcessRow(cosemStructure);
  }
}


