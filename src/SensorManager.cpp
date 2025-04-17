/*
 * SensorManager.cpp
 *
 *  Created on: Dec 17, 2024
 *      Author: olavt
 */

#include <cmath>
#include <platform/CHIPDeviceLayer.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/clusters/occupancy-sensor-server/occupancy-hal.h>
#include <app/clusters/occupancy-sensor-server/occupancy-sensor-server.h>
#include <platform/silabs/platformAbstraction/SilabsPlatform.h>

#include "sl_matter_sensor_config.h"
#include "silabs_utils.h"

#include <SensorManager.h>
#include "MeterManager.h"

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::DeviceLayer::Silabs;
using namespace chip::Protocols::InteractionModel;

constexpr chip::System::Clock::Milliseconds32 kSensorReadPeriod = chip::System::Clock::Milliseconds32(1000);

MeterManager meterManager;

namespace SensorManager
{

void SensorTimerTriggered(chip::System::Layer * aLayer, void * aAppState)
{
  UpdateMeters();

  aLayer->StartTimer(kSensorReadPeriod, SensorTimerTriggered, nullptr);
}

CHIP_ERROR Init()
{
    meterManager.Init();

    CHIP_ERROR status = CHIP_NO_ERROR;

    SensorTimerTriggered(&chip::DeviceLayer::SystemLayer(), nullptr);

    return status;
}

void UpdateMeters()
{
    meterManager.ReadMeters();
}

void ButtonActionTriggered(AppEvent * aEvent)
{
  UpdateMeters();
}

}





