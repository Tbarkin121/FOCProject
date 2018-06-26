/*------------------------------------------------------------------------------
* Copyright © Portal Instruments – All Rights Reserved
* Proprietary and Confidential
* Copying of this file or use of code contained in this file via any
* medium is strictly prohibited unless prior written permission is obtained
* from Portal Instruments, Inc.
* Created by Adam Casey 2016
------------------------------------------------------------------------------*/

#include "include/hardware.h"
#include "include/stm32f4xx.h"
// #include "include/gpio.h"
// #include "include/reset_and_clock_control.h"


std::error_code Hardware::Initialize() const {
	//led1_.Initialize();
    //led2_.Initialize();
    //led3_.Initialize();
    //led4_.Initialize();

	led1_notifier_.Initialize();
	led2_notifier_.Initialize();
	led3_notifier_.Initialize();
	// led4_notifier_.Initialize();

	IPWM::PWMConfig pwm_config_ = {
    .frequency_hz     =  5000,
    .min_duty_cycle   =  0.1f,
    .max_duty_cycle   =  0.9f,
    .min_output_value =  0.0f,  
    .max_output_value =  1.0f
	};
	led4_pwm_.Initialize(pwm_config_);
	led4_pwm_.Enable();
	return std::error_code();
}

// void Hardware::Fault(const std::error_code& fault) const {
//     __disable_irq();
//     BaseGPIOPin led_help_base_pin(rcc_, GPIOD, GPIO_PIN_12);
//     OutputPin help_pin(led_help_base_pin);
//     bool blink_led = true;

//     auto error = help_pin.Initialize();
//     if (error) {
//         blink_led = false;
//     }

//     // Set up help LED for blinking
//     const uint32_t BLINK_PERIOD = 1800000;
//     if (blink_led == true) {
//         help_pin.Set();
//     }

//     // Loop forever; blink the help LED and kick the watchdog just in case it got initialized
//     // If the watchdog was never initialized, the kick will just return without doing anything.
//     uint32_t spin_counter = 0;
//     while (1) {
//         if ( blink_led == true ) {
//             if (spin_counter == BLINK_PERIOD) {
//                 help_pin.Toggle();
//                 spin_counter = 0;
//             } else {
//                 spin_counter++;
//             }
//         }
//     }
// }
