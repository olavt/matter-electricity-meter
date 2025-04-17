/*
 * ElectricityMeter.cpp
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#include "ElectricityMeter.h"
#include "silabs_utils.h"

ElectricityMeter::ElectricityMeter(HanReader* hanReader)
{
  _hanReader = hanReader;
}

double ElectricityMeter::ActivePower()
{
  return _activePowerPlus;
}

double ElectricityMeter::CumulativeImportEnergy()
{
  return _cumulativeActiveImportEnergy;
}

std::string ElectricityMeter::MeterId()
{
  return _meterId;
}

std::string ElectricityMeter::MeterType()
{
  return _meterType;
}

void ElectricityMeter::UpdateActivePowerPlus(double watts)
{
  SILABS_LOG("Active power+ (Q1+Q4): %d Watt.", (int)watts);

  _activePowerPlus = watts;
  _activePowerPlusUpdated = true;
}

void ElectricityMeter::UpdateMeterId(std::string meterId)
{
  SILABS_LOG("Meter - Id: %s", meterId.c_str());
  if ((_meterId.length() > 0) && (meterId == _meterId))
    return;

  _meterId = meterId;
  _meterIdUpdated = true;
}

void ElectricityMeter::UpdateMeterType(std::string meterType)
{
  SILABS_LOG("Meter - type: %s", meterType.c_str());
  if ((meterType.length() > 0) && (meterType == _meterType))
    return;

  _meterType = meterType;
  _meterTypeUpdated = true;
}

void ElectricityMeter::UpdateCumulativeActiveImportEnergy(double kwh)
{
  SILABS_LOG("Cumulative hourly active import energy (A+) (Q1+Q4): %d wh.", (int)(kwh*1000));

  _cumulativeActiveImportEnergy = kwh;
  _cumulativeActiveImportEnergyUpdated = true;
}

void ElectricityMeter::UpdateInstantaneousVoltageL1(double volt)
{
  _instantaneousVoltageL1 = volt;
}

void ElectricityMeter::UpdateInstantaneousVoltageL2(double volt)
{
  _instantaneousVoltageL2 = volt;
}

void ElectricityMeter::UpdateInstantaneousVoltageL3(double volt)
{
  _instantaneousVoltageL3 = volt;
}


void ElectricityMeter::OnMeterDataProcessingCompleted()
{
  if (_activePowerPlusUpdated)
  {
      if (OnActivePowerUpdated)
        OnActivePowerUpdated();
      _activePowerPlusUpdated = false;
  }

  if (_cumulativeActiveImportEnergyUpdated)
  {
      if (OnCumulativeEnergyUpdated)
        OnCumulativeEnergyUpdated();
      _cumulativeActiveImportEnergyUpdated = false;
  }

  if (_meterIdUpdated)
  {
    if (OnMeterIdUpdated)
      OnMeterIdUpdated(_meterId);
    _meterIdUpdated = false;
  }

  if (_meterTypeUpdated)
  {
    if (OnMeterTypeUpdated)
      OnMeterTypeUpdated(_meterType);
    _meterTypeUpdated = false;
  }

}
