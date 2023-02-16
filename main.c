/** ***************************************************************************
 * @file    main.c
 * @brief   Simple LED Blink Demo for EFM32GG_STK3700
 * @version 1.0
 ******************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_chip.h"

#include "em_device.h"
#include "clock_efm32gg2.h"
#include "lcd.h"
#include "pwm.h"
#include "tt_tasks.h" /* 
                        Task_Init
                        Task_Add
                        Task_Dispatch
                        Task_Update */

#include "led.h" /*
                        LED_Toggle
                        LED_Init
                        */

#include "pwm.h" /*

                        */

#define SYSTICKDIVIDER 1000
#define SOFTDIVIDER 1000
#define DIVIDER 1000

#define IR_PORT gpioPortD
#define IR_PIN 0
#define PB0_PORT gpioPortB
#define PB0_PIN 9
#define PB1_PORT gpioPortB
#define PB1_PIN 10

/** ***************************************************************************
 * @brief  SysTick interrupt handler
 *
 * @note   Just calls Task_Update
 * @note   Called every 1 ms
 */

void SysTick_Handler(void)
{
    Task_Update();
}

int brightness_level,
    pwm_duty_cycle;

void update_led_brightness(void)
{
    if (brightness_level == 0)
        ;
    return;

    PWM_Write(TIMER0, 0, intensity);
    PWM_Write(TIMER0, 1, intensity);
    PWM_Write(TIMER0, 2, intensity);
}

void update_pwm_duty_cycle(void)
{
    LED_Toggle(LED2);
}

void update_color(void)
{
    return;
}
void CheckIRSensor(void)
{
    return;
}

/*****************************************************************************
 * @brief  Main function
 *
 * @note   Using default clock configuration
 *         HFCLK = HFRCO
 *         HFCORECLK = HFCLK
 *         HFPERCLK  = HFCLK
 */

int main(void)
{

    /* Configure LEDs */
    LED_Init(LED1 | LED2);

    (void) SystemCoreClockSet(CLOCK_HFXO,1,1);

    /* Initialize Task Kernel */
    Task_Init();
    Task_Add(update_led_brightness, 100, 0);
    Task_Add(update_pwm_duty_cycle, 100, 0);
    Task_Add(CheckIRSensor, 1, 0);

    /* Configure SysTick */
    SysTick_Config(SystemCoreClock / DIVIDER);

    /* Blink loop */
    while (1)
    {
        Task_Dispatch();
    }
}
