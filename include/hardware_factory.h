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
#include "include/pwm.h"
#include "include/i2c.h"
#include "include/MPU9250.h"
#include "include/AK8963.h"

class HardwareFactory {
 public:
    HardwareFactory() :
        led1_base_pin_(rcc_, GPIOA, GPIO_PIN_5),
        led2_base_pin_(rcc_, GPIOA, GPIO_PIN_6),
        led3_base_pin_(rcc_, GPIOA, GPIO_PIN_7),
        led4_base_pin_(rcc_, GPIOB, GPIO_PIN_6),

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

        // PWM
        led4_pwm_(rcc_, led4_base_pin_),

        //I2C
        sda_(rcc_, GPIOB, GPIO_PIN_9),
        scl_(rcc_, GPIOB, GPIO_PIN_8),
        testI2C_(rcc_, scl_, sda_),
        //IMU
        mpu9250_(testI2C_),
        ak8963_(testI2C_),

        hw_(rcc_,
            led1_pin_,
            led2_pin_,
            led3_pin_,
            led4_pin_,
        led1_notifier_,
        led2_notifier_,
        led3_notifier_,
        led4_notifier_,
        led4_pwm_,
        mpu9250_,
        ak8963_) {}

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

    // PWM
    PWM led4_pwm_;

    //I2C
    BaseGPIOPin sda_;
    BaseGPIOPin scl_;
    I2C testI2C_;

    //IMU
    MPU9250 mpu9250_;
    AK8963 ak8963_;

    Hardware hw_;
};

#endif  // INCLUDE_HARDWARE_FACTORY_H_
