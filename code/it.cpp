#include "it.h"

uint32_t utick = 0;//滴答定时器中断计数
uint32_t counter = 0;


void SysTick_Handler(void)
{

    SysTick->CTRL &= ~(1 << 16);

    utick++;
    if(utick%500 == 0)
		DL_GPIO_togglePins(GPIO_LEDS_PORT,GPIO_LEDS_USER_LED_1_PIN);

    task_handler();
}

void delay_ms(unsigned int ms)
{

    unsigned int tick = utick;

    while(utick < (tick + ms));

}






