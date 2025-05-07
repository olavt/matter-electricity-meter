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

  AidonElectricityMeter(std::unique_ptr<SerialPort> serialPort);

  void ReadFromHanPort();

private:

  void ProcessOBISListVersionIdentifier(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessMeterId(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessMeterType(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessActivePowerPlus(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessActivePowerMinus(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessReactivePowerPlus(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessReactivePowerMinus(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessCurrentPhaseL1(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessCurrentPhaseL2(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessCurrentPhaseL3(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessInstantaneousVoltageL1(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessInstantaneousVoltageL2(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessInstantaneousVoltageL3(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessMeterDateTime(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessCumulativeHourlyActiveImportEnergy(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessCumulativeHourlyActiveExportEnergy(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessCumulativeHourlyReactiveImportEnergy(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessCumulativeHourlyReactiveExportEnergy(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessRow(std::unique_ptr<CosemStructure>& cosemStructure);
  void ProcessMeterData(std::unique_ptr<CosemArray>& cosemArray);

};
