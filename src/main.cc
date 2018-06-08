#include "stm32f4xx.h"
#include "include/gpio.h"
#include "include/reset_and_clock_control.h"
#include "include/hardware_factory.h"
#include "include/hardware_interface.h"

int main(void)
{
  HardwareFactory hardware_factory;
  // IHardware& hw = hardware_factory.GetHardware();
  // hw.Initialize();
  // hw.Led1().Initialize();
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
      // hw.Led2().Toggle();
      // hw.Led3().Toggle();
      // hw.Led4().Toggle();
      hardware_factory.led1_pin_.Toggle();
      hardware_factory.led2_pin_.Toggle();
      hardware_factory.led3_pin_.Toggle();
      hardware_factory.led4_pin_.Toggle();
      HAL_Delay(1000);
    }

}