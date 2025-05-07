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

CHIP_ERROR Init()
{
    meterManager.Init();

    CHIP_ERROR status = CHIP_NO_ERROR;

    // Schedule the first execution of SensorTimerTriggered.
    // ScheduleWork is done to make sure it executes from the Matter task
    VerifyOrDieWithMsg(DeviceLayer::PlatformMgr().ScheduleWork([](intptr_t arg) {
      SensorTimerTriggered(&chip::DeviceLayer::SystemLayer(), nullptr);
    }) == CHIP_NO_ERROR,
                       AppServer, "Failed to schedule the first SensorCallback!");

    return status;
}

void UpdateMeters()
{
    meterManager.ReadMeters();
}

void SensorTimerTriggered(chip::System::Layer * aLayer, void * aAppState)
{
  UpdateMeters();

  aLayer->StartTimer(kSensorReadPeriod, SensorTimerTriggered, nullptr);
}

void ButtonActionTriggered(AppEvent * aEvent)
{
  UpdateMeters();
}

}





