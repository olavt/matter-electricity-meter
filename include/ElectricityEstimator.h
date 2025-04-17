/*
 * ElectricityEstimator.h
 *
 *  Created on: Feb 6, 2024
 *      Author: olavt
 */

#pragma once

#include<chrono>
#include<vector>

using namespace std::chrono;

class ElectricityEstimator
{

public:

  ElectricityEstimator();

  void AddWattsSample(double watts);

  double AverageWatts();

  void TopOfHourReset();

private:

  int _sampleCount;
  double _sumWatts;
  double _lastWatts;

};
