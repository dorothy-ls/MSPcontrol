#ifndef CONTROL_IT_H
#define CONTROL_IT_H

#include "ti_msp_dl_config.h"
//#include "config.h"
#include "task.h"
//#include "QEI.h"
//#include "module.h"



#ifdef __cplusplus
extern "C" {
#endif

extern uint32_t utick;

void SysTick_Handler(void);

void delay_ms(unsigned int ms);

//void TIM_ENCODE_INST_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif
