/*------------------------------------------------------------------------------
* Copyright © Portal Instruments – All Rights Reserved
* Proprietary and Confidential
* Copying of this file or use of code contained in this file via any
* medium is strictly prohibited unless prior written permission is obtained
* from Portal Instruments, Inc.
* Created by Adam Casey 2016
------------------------------------------------------------------------------*/

#ifndef INCLUDE_HARDWARE_H_
#define INCLUDE_HARDWARE_H_

#include "include/hardware_interface.h"

#include "include/gpio_interface.h"
#include "include/reset_and_clock_control_interface.h"
#include "include/led_notifier_interface.h"

class Hardware : public IHardware {
 public:
        Hardware(const IResetAndClockControl& rcc,
                 const IOutputPin& led1,
                 const IOutputPin& led2,
                 const IOutputPin& led3,
                 const IOutputPin& led4,
                 const ILedNotifier& led1_notifier,
                 const ILedNotifier& led2_notifier,
                 const ILedNotifier& led3_notifier,
                 const ILedNotifier& led4_notifier)
                 : rcc_(rcc),
                   led1_(led1),
                   led2_(led2),
                   led3_(led3),
                   led4_(led4),
                   led1_notifier_(led1_notifier),
                   led2_notifier_(led2_notifier),
                   led3_notifier_(led3_notifier),
                   led4_notifier_(led4_notifier) {}

        std::error_code Initialize() const;
        const IResetAndClockControl& ResetAndClockControl() const { return rcc_; }
        const IOutputPin& Led1() const { return led1_; }
        const IOutputPin& Led2() const { return led2_; }
        const IOutputPin& Led3() const { return led3_; }
        const IOutputPin& Led4() const { return led4_; }
        const ILedNotifier& Led1Notifier() const { return led1_notifier_; }
        const ILedNotifier& Led2Notifier() const { return led2_notifier_; }
        const ILedNotifier& Led3Notifier() const { return led3_notifier_; }
        const ILedNotifier& Led4Notifier() const { return led4_notifier_; }

 protected:
        const IResetAndClockControl& rcc_;
        const IOutputPin& led1_;
        const IOutputPin& led2_;
        const IOutputPin& led3_;
        const IOutputPin& led4_;
        const ILedNotifier& led1_notifier_;
        const ILedNotifier& led2_notifier_;
        const ILedNotifier& led3_notifier_;
        const ILedNotifier& led4_notifier_;
};

#endif  // INCLUDE_HARDWARE_H_
