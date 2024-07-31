
#include "ti_msp_dl_config.h"
#include "task.h"

/* This results in approximately 0.5s of delay assuming 32MHz CPU_CLK */
#define DELAY (16000000)

//unsigned int utick = 0;//滴答定时器中断计数
//unsigned int counter = 0;
//void SysTick_Handler(void)
//{
//
//  SysTick->CTRL &= ~(1 << 16); /*清除滴答定时器中断标志位*/
//
//  utick++;//滴答定时器中断计数
//  if(utick%1000 == 0)
//  DL_GPIO_togglePins(GPIO_LEDS_PORT,
//              GPIO_LEDS_USER_LED_1_PIN | GPIO_LEDS_USER_LED_2_PIN |
//                  GPIO_LEDS_USER_LED_3_PIN | GPIO_LEDS_USER_TEST_PIN);
//
//}
//
//void delay_ms(unsigned int ms)
//
//{
//
//unsigned int tick = utick;
//
//while(utick < (tick + ms));
//
//}

int main(void)
{
    SYSCFG_DL_init();

    setup();

    while (1) {

        loop();
    }
}
