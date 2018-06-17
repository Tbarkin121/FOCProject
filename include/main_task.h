/*------------------------------------------------------------------------------
* Copyright © Portal Instruments – All Rights Reserved
* Proprietary and Confidential
* Copying of this file or use of code contained in this file via any
* medium is strictly prohibited unless prior written permission is obtained
* from Portal Instruments, Inc.
* Created by Joseph McLaughlin 2017
------------------------------------------------------------------------------*/

#ifndef INCLUDE_MAIN_TASK_H_
#define INCLUDE_MAIN_TASK_H_

#include "include/rtos_task.h"
#include "include/hardware_factory.h"
#include "include/hardware_interface.h"

static constexpr int MAIN_STACK_LENGTH = 24 * 1024;

//-----------------------------------------------------------------------------
template <typename HardwareFactoryType>
class MainTask : public RTOSTask<MainTask<HardwareFactoryType>, MAIN_STACK_LENGTH> {
 public:
    class EventHandler : public TaskEventHandler {
     public:
        void MainTaskLoop(const MainTask& task) {
            HardwareFactoryType hardwareFactory;
            IHardware& hw = hardwareFactory.GetHardware();

            hw.Initialize();

            TaskEventHandler::MainLoop(task);
        }
    };

    MainTask() : RTOSTask<MainTask<HardwareFactoryType>, MAIN_STACK_LENGTH>(
                    "MAIN", PRIORITY, std::bind(&EventHandler::MainTaskLoop,
                    &event_handler_, std::placeholders::_1)) {}

 protected:
    static constexpr int PRIORITY = configMAX_PRIORITIES - 1;
    EventHandler event_handler_;
};

#endif  // INCLUDE_MAIN_TASK_H_
