#include "it.h"

uint32_t utick = 0;//滴答定时器中断计数
uint32_t counter = 0;


void SysTick_Handler(void)
{

    SysTick->CTRL &= ~(1 << 16); /*清除滴答定时器中断标志位*/

    utick++;//滴答定时器中断计数
    if(utick%1000 == 0)
    DL_GPIO_togglePins(GPIO_LEDS_PORT,GPIO_LEDS_USER_LED_1_PIN);

    task_handler();
}

void delay_ms(unsigned int ms)
{

unsigned int tick = utick;

while(utick < (tick + ms));

}

//编码器定时器IRQ，读编码器GPIO输入并计数

//void TIM_ENCODE_INST_IRQHandler(void)
//{
//    //TIM_QEI_Handler_LEFT();
//    //TIM_QEI_Handler_RIGHT();
//}





