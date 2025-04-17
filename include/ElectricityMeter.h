/*
 * ElectricityMeter.h
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#pragma once

#include <functional>

#include "ElectricityEstimator.h"
#include "Hanreader.h"

class ElectricityMeter
{

public:

  ElectricityMeter(HanReader* hanReader);

  // Return Active Power in Watts
  double ActivePower();

  // Return Cumulative Import Energy in kWh
  double CumulativeImportEnergy();

  std::string MeterId();

  std::string MeterType();

  // Pure Virtual Function
  virtual void ReadFromHanPort() = 0;

  // Updated every 2.5 seconds
  std::function<void()> OnActivePowerUpdated;

  std::function<void(std::string meterId)> OnMeterIdUpdated;

  std::function<void(std::string meterType)> OnMeterTypeUpdated;

  std::function<void()> OnCumulativeEnergyUpdated;

protected:

  void UpdateActivePowerPlus(double watts);

  void UpdateMeterId(std::string meterId);

  void UpdateMeterType(std::string meterId);

  void UpdateCumulativeActiveImportEnergy(double kwh);

  void UpdateInstantaneousVoltageL1(double volt);

  void UpdateInstantaneousVoltageL2(double volt);

  void UpdateInstantaneousVoltageL3(double volt);

  void OnMeterDataProcessingCompleted();

  HanReader* _hanReader;
  ElectricityEstimator _electricityEstimator;

private:

  double _activePowerPlus;
  bool _activePowerPlusUpdated = false;

  double _cumulativeActiveImportEnergy = 0.0;
  bool _cumulativeActiveImportEnergyUpdated = false;

  double _instantaneousVoltageL1 = 0.0;
  double _instantaneousVoltageL2 = 0.0;
  double _instantaneousVoltageL3 = 0.0;

  std::string _meterId;
  bool _meterIdUpdated = false;

  std::string _meterType;
  bool _meterTypeUpdated = false;

};
