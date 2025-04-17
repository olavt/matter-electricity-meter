/*
 * ElectrictyEstimator.cpp
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#include "ElectricityEstimator.h"
#include<chrono>

using namespace std::chrono;

ElectricityEstimator::ElectricityEstimator()
{
  _sampleCount = 0;
  _lastWatts = 0;
}

void ElectricityEstimator::AddWattsSample(double watts)
{
  _lastWatts = watts;
  _sumWatts += watts;
  _sampleCount++;
}

double ElectricityEstimator::AverageWatts()
{
  if (_sampleCount == 0)
    return _lastWatts;

  double averageWatts = (_sumWatts / _sampleCount);

  return averageWatts;
}

void ElectricityEstimator::TopOfHourReset()
{
  _sampleCount = 0;
  _sumWatts = 0;
}
