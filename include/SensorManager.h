/*
 * SensorManagerCustom.h
 *
 *  Created on: Dec 17, 2024
 *      Author: olavt
 */

#pragma once

#include <lib/core/CHIPError.h>
#include "AppEvent.h"

namespace SensorManager
{

  CHIP_ERROR Init();

  void UpdateMeters();

  void SensorTimerTriggered(chip::System::Layer * aLayer, void * aAppState);

  void ButtonActionTriggered(AppEvent * aEvent);

};
