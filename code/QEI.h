//���MSPM0G350x����һ��QEI TIM�����������4·GPIO���빹���������������

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
