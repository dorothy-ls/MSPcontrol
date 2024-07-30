#ifndef CONTROL_TASK_H
#define CONTROL_TASK_H

#include "ti_msp_dl_config.h"


#ifdef __cplusplus
extern "C" {
#endif

void setup();

void loop();

void task_handler();

void UART_0_INST_IRQHandler(void);

void TIM_CCD_INST_IRQHandler(void);

void ADC_CCD_INST_IRQHandler(void);

void GROUP1_IRQHandler(void);

void ADC_VIN_INST_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif
