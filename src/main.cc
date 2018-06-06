#include "stm32f4xx.h"
#include "include/gpio.h"
#include "include/reset_and_clock_control.h"

int main(void)
{
    //__disable_irq();
    ResetAndClockControl rcc;
    // set the buck into normal operating mode.
    BaseGPIOPin led1_base_pin(rcc, GPIOD, GPIO_PIN_12);
    OutputPin led1_pin(led1_base_pin);
    led1_pin.Initialize();
    led1_pin.Set();

    BaseGPIOPin led2_base_pin(rcc, GPIOD, GPIO_PIN_13);
    OutputPin led2_pin(led2_base_pin);
    led2_pin.Initialize();
    led2_pin.Set();

    BaseGPIOPin led3_base_pin(rcc, GPIOD, GPIO_PIN_14);
    OutputPin led3_pin(led3_base_pin);
    led3_pin.Initialize();
    led3_pin.Set();

    BaseGPIOPin led4_base_pin(rcc, GPIOD, GPIO_PIN_15);
    OutputPin led4_pin(led4_base_pin);
    led4_pin.Initialize();
    led4_pin.Set();

    while(1){

    }
}
