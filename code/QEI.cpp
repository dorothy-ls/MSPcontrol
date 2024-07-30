#include "QEI.h"
//虚拟CNT，模拟编码器TIM的CNT寄存器，16位
uint16_t LEFT_CNT = 0;
uint16_t RIGHT_CNT = 0;
//虚拟溢出中断标志位，实际用回调函数实现
uint8_t left_overflow_flag = 0;
uint8_t right_overflow_flag = 0;
//两路软件QEI溢出回调声明
void (*LEFT_QEI_callback)();
void (*RIGHT_QEI_callback)();
//回调注册函数
void register_LEFT_QEI_callback(void(*cb)())
{
    LEFT_QEI_callback = cb;
}
void register_RIGHT_QEI_callback(void(*cb)())
{
    RIGHT_QEI_callback = cb;
}
//volatile uint32_t gpioA;
//volatile uint32_t gpioB;
//定时器中断中调用，读取GPIO输入并计数
/*
void TIM_QEI_Handler_LEFT(void)
{
    static uint32_t prev_LEFT_B = 0;
    static uint32_t curr_LEFT_A = 0;
    static uint32_t curr_LEFT_B = 0;
    curr_LEFT_A = DL_GPIO_readPins(GPIO_ENCODE_PORT,GPIO_ENCODE_LEFT_A_PIN);
    curr_LEFT_B = DL_GPIO_readPins(GPIO_ENCODE_PORT,GPIO_ENCODE_LEFT_B_PIN);


    uint16_t temp_CNT = LEFT_CNT;

    if(curr_LEFT_A == 0)
    {

        if(prev_LEFT_B !=0 && curr_LEFT_B == 0)
            LEFT_CNT ++;
        else if(prev_LEFT_B ==0 && curr_LEFT_B != 0)
            LEFT_CNT --;
    }
    else
    {
        if(prev_LEFT_B !=0 && curr_LEFT_B == 0)
            LEFT_CNT --;
        else if(prev_LEFT_B ==0 && curr_LEFT_B != 0)
            LEFT_CNT ++;
    }

    if((temp_CNT == 65535 && LEFT_CNT == 0) || (temp_CNT == 0 && LEFT_CNT == 65535))
        LEFT_QEI_callback();

    prev_LEFT_B = curr_LEFT_B;
}

void TIM_QEI_Handler_RIGHT(void)
{
    static uint32_t prev_RIGHT_A = 0;
    static uint32_t prev_RIGHT_B = 0;
    static uint32_t curr_RIGHT_A = 0;
    static uint32_t curr_RIGHT_B = 0;
    curr_RIGHT_A = DL_GPIO_readPins(GPIO_ENCODE_PORT,GPIO_ENCODE_RIGHT_A_PIN);
    curr_RIGHT_B = DL_GPIO_readPins(GPIO_ENCODE_PORT,GPIO_ENCODE_RIGHT_B_PIN);

    /*uint16_t temp_CNT = RIGHT_CNT;

    if(curr_RIGHT_A == 0)
    {
        if(prev_RIGHT_B !=0 && curr_RIGHT_B == 0)
            RIGHT_CNT ++;
        if(prev_RIGHT_B ==0 && curr_RIGHT_B != 0)
            RIGHT_CNT --;
    }
    else if(curr_RIGHT_A != 0)
    {
        if(prev_RIGHT_B !=0 && curr_RIGHT_B == 0)
            RIGHT_CNT --;
        if(prev_RIGHT_B ==0 && curr_RIGHT_B != 0)
            RIGHT_CNT ++;
    }

    if(temp_CNT == 65535 && RIGHT_CNT == 0 || temp_CNT == 0 && RIGHT_CNT == 65535)
        RIGHT_QEI_callback();

    prev_RIGHT_A = curr_RIGHT_A;
    prev_RIGHT_B = curr_RIGHT_B;
}*/
//uint32_t GPIO_IRQ_cnt = 0;
//void GROUP1_IRQHandler(void)
//{
//    GPIO_IRQ_cnt ++;
//    //获取中断信号
//    gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA,GPIO_ENCODE_L_LEFT_A_PIN | GPIO_ENCODE_L_LEFT_B_PIN);
//    gpioB = DL_GPIO_getEnabledInterruptStatus(GPIOB,GPIO_ENCODE_R_RIGHT_A_PIN | GPIO_ENCODE_R_RIGHT_B_PIN);
//
//    //如果是GPIO_EncoderA_PIN_0_PIN产生的中断
//    if((gpioA & GPIO_ENCODE_L_LEFT_A_PIN) == GPIO_ENCODE_L_LEFT_A_PIN)
//    {
//        //Pin0上升沿，看Pin1的电平，为低电平则判断为反转，高电平判断为正转
//        if(!DL_GPIO_readPins(GPIOA,GPIO_ENCODE_L_LEFT_B_PIN))//P1为低电平
//        {
//            LEFT_CNT--;
//        }
//        else//P1为高电平
//        {
//            LEFT_CNT++;
//        }
//    }
//
//    //类似于Stm32中编码器模式的AB两相都测，可得到2倍的计数
//    else if((gpioA & GPIO_ENCODE_L_LEFT_B_PIN) == GPIO_ENCODE_L_LEFT_B_PIN)
//    {
//        //Pin1上升沿
//        if(!DL_GPIO_readPins(GPIOA,GPIO_ENCODE_L_LEFT_A_PIN))//P0为低电平
//        {
//            LEFT_CNT++;
//        }
//        else//P1为高电平
//        {
//            LEFT_CNT--;
//        }
//    }
//
//    if((gpioB & GPIO_ENCODE_R_RIGHT_A_PIN) == GPIO_ENCODE_R_RIGHT_A_PIN)
//    {
//        //Pin0上升沿，看Pin1的电平，为低电平则判断为反转，高电平判断为正转
//        if(!DL_GPIO_readPins(GPIOB,GPIO_ENCODE_R_RIGHT_B_PIN))//P1为低电平
//        {
//            RIGHT_CNT--;
//        }
//        else//P1为高电平
//        {
//            RIGHT_CNT++;
//        }
//    }
//
//    //类似于Stm32中编码器模式的AB两相都测，可得到2倍的计数
//    else if((gpioB & GPIO_ENCODE_R_RIGHT_B_PIN) == GPIO_ENCODE_R_RIGHT_B_PIN)
//    {
//        //Pin1上升沿
//        if(!DL_GPIO_readPins(GPIOB,GPIO_ENCODE_R_RIGHT_A_PIN))//P0为低电平
//        {
//            RIGHT_CNT++;
//        }
//        else//P1为高电平
//        {
//            RIGHT_CNT--;
//        }
//    }
//
//    //最后清除中断标志位
//    DL_GPIO_clearInterruptStatus(GPIOA, GPIO_ENCODE_L_LEFT_A_PIN | GPIO_ENCODE_L_LEFT_B_PIN);
//    DL_GPIO_clearInterruptStatus(GPIOB, GPIO_ENCODE_R_RIGHT_A_PIN | GPIO_ENCODE_R_RIGHT_B_PIN);
//}
