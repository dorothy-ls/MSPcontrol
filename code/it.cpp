#include "it.h"

uint32_t utick = 0;//�δ�ʱ���жϼ���
uint32_t counter = 0;


void SysTick_Handler(void)
{

    SysTick->CTRL &= ~(1 << 16); /*����δ�ʱ���жϱ�־λ*/

    utick++;//�δ�ʱ���жϼ���
    if(utick%1000 == 0)
    DL_GPIO_togglePins(GPIO_LEDS_PORT,GPIO_LEDS_USER_LED_1_PIN);

    task_handler();
}

void delay_ms(unsigned int ms)
{

unsigned int tick = utick;

while(utick < (tick + ms));

}

//��������ʱ��IRQ����������GPIO���벢����

//void TIM_ENCODE_INST_IRQHandler(void)
//{
//    //TIM_QEI_Handler_LEFT();
//    //TIM_QEI_Handler_RIGHT();
//}





