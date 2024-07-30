//针对MSPM0G350x仅有一个QEI TIM的软件补丁，4路GPIO输入构建两个软件编码器

#ifndef CONTROL_QEI_H
#define CONTROL_QEI_H

#include "ti_msp_dl_config.h"

extern uint16_t LEFT_CNT;
extern uint16_t RIGHT_CNT;
void TIM_QEI_Handler_LEFT(void);
void TIM_QEI_Handler_RIGHT(void);
void register_LEFT_QEI_callback(void(*cb)());
void register_RIGHT_QEI_callback(void(*cb)());
//void GROUP1_IRQHandler(void);
#endif
