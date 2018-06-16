#include "stm32f4xx.h"
#include "include/gpio.h"
#include "include/reset_and_clock_control.h"
#include "include/hardware_factory.h"
#include "include/hardware_interface.h"

static ResetAndClockControl rcc;

int main(void)
{
  HardwareFactory hardware_factory;
  IHardware& hw = hardware_factory.GetHardware();
  hw.Initialize();
  hw.Led1().Set();
  hw.Led2().Set();
  hw.Led3().Set();
  hw.Led4().Set();

 

    rcc.InitializeHardware();



    /* If all is well, the scheduler will now be running, and the following line
    will never be reached.  If the following line does execute, then there was
    insufficient FreeRTOS heap memory available for the idle and/or timer tasks
    to be created.  See the memory management section on the FreeRTOS web site
    for more details. */
    while(1){
      hw.Led1().Toggle();
      hw.Led2().Toggle();
      hw.Led3().Toggle();
      hw.Led4().Toggle();

      HAL_Delay(1000);
    }

}
