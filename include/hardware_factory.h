/*------------------------------------------------------------------------------
* Copyright © Portal Instruments – All Rights Reserved
* Proprietary and Confidential
* Copying of this file or use of code contained in this file via any
* medium is strictly prohibited unless prior written permission is obtained
* from Portal Instruments, Inc.
* Created by Jason Braley 2017
------------------------------------------------------------------------------*/

#ifndef INCLUDE_HARDWARE_FACTORY_H_
#define INCLUDE_HARDWARE_FACTORY_H_

#include "include/hardware.h"
#include "include/reset_and_clock_control.h"
#include "include/gpio.h"
#include "include/simple_led_notifier.h"


class HardwareFactory {
 public:
    HardwareFactory() :
        led1_base_pin_(rcc_, GPIOD, GPIO_PIN_12),
        led2_base_pin_(rcc_, GPIOD, GPIO_PIN_13),
        led3_base_pin_(rcc_, GPIOD, GPIO_PIN_14),
        led4_base_pin_(rcc_, GPIOD, GPIO_PIN_15),

        led1_pin_(led1_base_pin_),
        led2_pin_(led2_base_pin_),
        led3_pin_(led3_base_pin_),
        led4_pin_(led4_base_pin_),
        
        led1_notifier_({
            &led1_pin_
        }),
        led2_notifier_({
            &led2_pin_
        }),
        led3_notifier_({
            &led3_pin_
        }),
        led4_notifier_({
            &led4_pin_
        }),

        hw_(rcc_,
            led1_pin_,
            led2_pin_,
            led3_pin_,
            led4_pin_,
        led1_notifier_,
        led2_notifier_,
        led3_notifier_,
        led4_notifier_) {}

    IHardware& GetHardware() { return hw_; }

 // private:
    // System Level
    ResetAndClockControl rcc_;

    // LEDs
    BaseGPIOPin led1_base_pin_;
    BaseGPIOPin led2_base_pin_;
    BaseGPIOPin led3_base_pin_;
    BaseGPIOPin led4_base_pin_;

    OutputPin led1_pin_;
    OutputPin led2_pin_;
    OutputPin led3_pin_;
    OutputPin led4_pin_;

    SimpleLedNotifier led1_notifier_;
    SimpleLedNotifier led2_notifier_;
    SimpleLedNotifier led3_notifier_;
    SimpleLedNotifier led4_notifier_;

    Hardware hw_;
};

#endif  // INCLUDE_HARDWARE_FACTORY_H_
