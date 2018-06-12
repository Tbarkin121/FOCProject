#include "stm32f4xx.h"
#include "include/gpio.h"
#include "include/reset_and_clock_control.h"
#include "include/hardware_factory.h"
#include "include/hardware_interface.h"

#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

static ResetAndClockControl rcc;

static void led_control_task(void *parameters);
static void timer_control_task(void *parameters);

static EventGroupHandle_t led_control_event_group_handle;
static StaticEventGroup_t led_control_event_group;

#define LED_CONTROL_STACK_SIZE 128
static StaticTask_t led_control_task_tcb;
static StackType_t led_control_task_stack[LED_CONTROL_STACK_SIZE];
static TaskHandle_t led_control_task_handle;

#define TIMER_CONTROL_STACK_SIZE 128
static StaticTask_t timer_control_task_tcb;
static StackType_t timer_control_task_stack[TIMER_CONTROL_STACK_SIZE];
static TaskHandle_t timer_control_task_handle;

int main(void)
{
  HardwareFactory hardware_factory;
  IHardware& hw = hardware_factory.GetHardware();
  hw.Initialize();
  hw.Led1().Clear();
  hw.Led2().Clear();
  hw.Led3().Clear();
  hw.Led4().Clear();

  // Spawn the task that controls LED timing
    timer_control_task_handle = xTaskCreateStatic(
        timer_control_task,
        "timer",
        TIMER_CONTROL_STACK_SIZE,
        NULL,
        (configMAX_PRIORITIES - 2),
        timer_control_task_stack,
        &timer_control_task_tcb);

    // Spawn the task that turns the LED on/off
    led_control_task_handle = xTaskCreateStatic(
        led_control_task,
        "led",
        LED_CONTROL_STACK_SIZE,
        NULL,
        (configMAX_PRIORITIES - 2),
        led_control_task_stack,
        &led_control_task_tcb);

    // Create the event group for sending events from the timer task to the
    // led task
    led_control_event_group_handle = xEventGroupCreateStatic(&led_control_event_group);

    rcc.InitializeHardware();

    // Start the scheduler
    vTaskStartScheduler();

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


// Event bit definititions for led_control_event_group_handle
#define LED_ON_EVENT_BIT    (EventBits_t)(1 << 0)
#define LED_OFF_EVENT_BIT   (EventBits_t)(1 << 1)
#define ALL_EVENT_BITS      (EventBits_t)(LED_ON_EVENT_BIT | LED_OFF_EVENT_BIT)

// Controls the timing / duty cycle of the blinking LED with FreeRTOS
// vTaskDelay(); Sends events to the led control task to request
// turning on/off the LED
static void timer_control_task(void *parameters) {
    while (1) {
        // A double-blink to differentiate from non-OS blinky app
        xEventGroupSetBits(led_control_event_group_handle, LED_ON_EVENT_BIT);
        vTaskDelay(100);

        xEventGroupSetBits(led_control_event_group_handle, LED_OFF_EVENT_BIT);
        vTaskDelay(100);

        xEventGroupSetBits(led_control_event_group_handle, LED_ON_EVENT_BIT);
        vTaskDelay(100);

        xEventGroupSetBits(led_control_event_group_handle, LED_OFF_EVENT_BIT);
        vTaskDelay(700);
    }
}

// Waits for events from the timer_control_task and turns the LED
// on/off on when requested.
static void led_control_task(void *parameters) {
    HardwareFactory hardware_factory;
    IHardware& hw = hardware_factory.GetHardware();
    hw.Initialize();
    bool blink_led = true;


    while (1) {
        // Wait for an event from the timer control task.
        EventBits_t event_bits = xEventGroupWaitBits(
                    led_control_event_group_handle,
                    ALL_EVENT_BITS,
                    pdTRUE,         /* clear bits after reading */
                    pdFALSE,        /* wait for ANY of the events to occur */
                    1000);          /* timeout in milliseconds */

        if (blink_led) {
            if (event_bits & LED_ON_EVENT_BIT) {
                hw.Led1().Set();
                hw.Led2().Set();
                hw.Led3().Set();
                hw.Led4().Set();
            }
            if (event_bits & LED_OFF_EVENT_BIT) {
                hw.Led1().Clear();
                hw.Led2().Clear();
                hw.Led3().Clear();
                hw.Led4().Clear();
            }
        }
    }
}

#if (configUSE_TICK_HOOK == 1)
extern "C" void vApplicationTickHook() {
}
#endif // (configUSE_TICK_HOOK == 1)
