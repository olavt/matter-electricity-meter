/*
 * AidonElectricityMeter.h
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#pragma once

#include "AidonHanReader.h"
#include "ElectricityMeter.h"
#include "CosemArray.h"
#include "CosemObject.h"
#include "CosemOctetString.h"
#include "CosemStructure.h"

class AidonElectricityMeter : public ElectricityMeter
{

public:

  AidonElectricityMeter(SerialPort* serialPort);

  void ReadFromHanPort();

private:

  AidonHanReader* CreateHanReader(SerialPort* serialPort);

  void ProcessOBISListVersionIdentifier(CosemStructure* cosemStructure);

  void ProcessMeterId(CosemStructure* cosemStructure);

  void ProcessMeterType(CosemStructure* cosemStructure);

  void ProcessActivePowerPlus(CosemStructure* cosemStructure);

  void ProcessActivePowerMinus(CosemStructure* cosemStructure);

  void ProcessReactivePowerPlus(CosemStructure* cosemStructure);

  void ProcessReactivePowerMinus(CosemStructure* cosemStructure);

  void ProcessCurrentPhaseL1(CosemStructure* cosemStructure);

  void ProcessCurrentPhaseL2(CosemStructure* cosemStructure);

  void ProcessCurrentPhaseL3(CosemStructure* cosemStructure);

  void ProcessInstantaneousVoltageL1(CosemStructure* cosemStructure);

  void ProcessInstantaneousVoltageL2(CosemStructure* cosemStructure);

  void ProcessInstantaneousVoltageL3(CosemStructure* cosemStructure);

  void ProcessMeterDateTime(CosemStructure* cosemStructure);

  void ProcessCumulativeHourlyActiveImportEnergy(CosemStructure* cosemStructure);

  void ProcessCumulativeHourlyActiveExportEnergy(CosemStructure* cosemStructure);

  void ProcessCumulativeHourlyReactiveImportEnergy(CosemStructure* cosemStructure);

  void ProcessCumulativeHourlyReactiveExportEnergy(CosemStructure* cosemStructure);

  void ProcessRow(CosemStructure* cosemStructure);

  void ProcessMeterData(CosemArray* cosemArray);

};
