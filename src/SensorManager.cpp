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

namespace SensorManager
{

constexpr chip::System::Clock::Milliseconds32 kSensorReadPeriod = chip::System::Clock::Milliseconds32(1000);

MeterManager meterManager;


CHIP_ERROR Init()
{
    meterManager.Init();

    SILABS_LOG("Init: Calling StartTimer");
    CHIP_ERROR status = chip::DeviceLayer::SystemLayer().StartTimer(chip::System::Clock::Milliseconds32(30000), SensorTimerCallback, nullptr);
    if (status != CHIP_NO_ERROR) {
        SILABS_LOG("Init: StartTimer returned error: %s.", chip::ErrorStr(status));
    }

    return status;
}

void UpdateMeters()
{
    meterManager.ReadMeters();
}

void ProcessMeterDataCallback(intptr_t context)
{
  SILABS_LOG("ProcessMeterDataCallback: Started to execute.");

  UpdateMeters();

  SILABS_LOG("ProcessMeterDataCallback: Finished executing.");
}

void SensorTimerCallback(chip::System::Layer* aLayer, void* aAppState)
{
  SILABS_LOG("SensorTimerCallback: Started to execute.");

  // Schedule the data processing in the Matter event loop
  CHIP_ERROR status = chip::DeviceLayer::PlatformMgr().ScheduleWork(ProcessMeterDataCallback, reinterpret_cast<intptr_t>(nullptr));
  if (status != CHIP_NO_ERROR) {
      SILABS_LOG("SensorTimerCallback: Failed to schedule work: %s", chip::ErrorStr(status));
  }

  SILABS_LOG("SensorTimerCallback: Calling StartTimer");
  status = aLayer->StartTimer(kSensorReadPeriod, SensorTimerCallback, nullptr);
  if (status != CHIP_NO_ERROR) {
      SILABS_LOG("SensorTimerCallback: StartTimer returned error: %s.", chip::ErrorStr(status));
  }

  SILABS_LOG("SensorTimerCallback: Finished executing.");
  SILABS_LOG("");
}

void ButtonActionTriggered(AppEvent * aEvent)
{
  UpdateMeters();
}

}





