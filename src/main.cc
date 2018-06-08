#include "stm32f4xx.h"
#include "include/gpio.h"
#include "include/hardware_factory.h"


void delay_cycles(uint32_t cyclecount) {
    volatile uint32_t spin_counter = 0;
    while(1)
    {
        if (spin_counter == cyclecount) {
            break;
            } else {
            spin_counter++;
        }
    }
}

int main(void)
{
  HardwareFactory hardware_factory;
  // IHardware& hw = hardware_factory.GetHardware();
  // hw.Initialize();
  // hw.Led1().Set();
  // hw.Led2().Set();
  // hw.Led3().Set();
  // hw.Led4().Set();
  
  hardware_factory.led1_pin_.Initialize();
  hardware_factory.led2_pin_.Initialize();
  hardware_factory.led3_pin_.Initialize();
  hardware_factory.led4_pin_.Initialize();
  hardware_factory.led1_pin_.Set();
  hardware_factory.led2_pin_.Clear();
  hardware_factory.led3_pin_.Set();
  hardware_factory.led4_pin_.Clear();

    while(1){
      // hw.Led1().Toggle();
      // delay_cycles(1);
      // // hw.Led2().Toggle();
      // delay_cycles(1);
      // // hw.Led3().Toggle();
      // delay_cycles(1);
      // // hw.Led4().Toggle();
      // delay_cycles(10000);
      hardware_factory.led1_pin_.Toggle();
      hardware_factory.led2_pin_.Toggle();
      hardware_factory.led3_pin_.Toggle();
      hardware_factory.led4_pin_.Toggle();
      // HAL_Delay(1);
      //

    }

}
