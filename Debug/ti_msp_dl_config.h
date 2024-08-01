/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_MOTOR0 */
#define PWM_MOTOR0_INST                                                    TIMA0
#define PWM_MOTOR0_INST_IRQHandler                              TIMA0_IRQHandler
#define PWM_MOTOR0_INST_INT_IRQN                                (TIMA0_INT_IRQn)
#define PWM_MOTOR0_INST_CLK_FREQ                                        80000000
/* GPIO defines for channel 2 */
#define GPIO_PWM_MOTOR0_C2_PORT                                            GPIOB
#define GPIO_PWM_MOTOR0_C2_PIN                                    DL_GPIO_PIN_20
#define GPIO_PWM_MOTOR0_C2_IOMUX                                 (IOMUX_PINCM48)
#define GPIO_PWM_MOTOR0_C2_IOMUX_FUNC                IOMUX_PINCM48_PF_TIMA0_CCP2
#define GPIO_PWM_MOTOR0_C2_IDX                               DL_TIMER_CC_2_INDEX
/* GPIO defines for channel 3 */
#define GPIO_PWM_MOTOR0_C3_PORT                                            GPIOA
#define GPIO_PWM_MOTOR0_C3_PIN                                    DL_GPIO_PIN_28
#define GPIO_PWM_MOTOR0_C3_IOMUX                                  (IOMUX_PINCM3)
#define GPIO_PWM_MOTOR0_C3_IOMUX_FUNC                 IOMUX_PINCM3_PF_TIMA0_CCP3
#define GPIO_PWM_MOTOR0_C3_IDX                               DL_TIMER_CC_3_INDEX

/* Defines for TIM_CCD */
#define TIM_CCD_INST                                                      TIMG12
#define TIM_CCD_INST_IRQHandler                                TIMG12_IRQHandler
#define TIM_CCD_INST_INT_IRQN                                  (TIMG12_INT_IRQn)
#define TIM_CCD_INST_CLK_FREQ                                           80000000
/* GPIO defines for channel 1 */
#define GPIO_TIM_CCD_C1_PORT                                               GPIOA
#define GPIO_TIM_CCD_C1_PIN                                       DL_GPIO_PIN_31
#define GPIO_TIM_CCD_C1_IOMUX                                     (IOMUX_PINCM6)
#define GPIO_TIM_CCD_C1_IOMUX_FUNC                   IOMUX_PINCM6_PF_TIMG12_CCP1
#define GPIO_TIM_CCD_C1_IDX                                  DL_TIMER_CC_1_INDEX

/* Publisher defines */
#define TIM_CCD_INST_PUB_0_CH                                                (1)

/* Defines for PWM_MOTOR1 */
#define PWM_MOTOR1_INST                                                    TIMA1
#define PWM_MOTOR1_INST_IRQHandler                              TIMA1_IRQHandler
#define PWM_MOTOR1_INST_INT_IRQN                                (TIMA1_INT_IRQn)
#define PWM_MOTOR1_INST_CLK_FREQ                                        80000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_MOTOR1_C0_PORT                                            GPIOB
#define GPIO_PWM_MOTOR1_C0_PIN                                     DL_GPIO_PIN_4
#define GPIO_PWM_MOTOR1_C0_IOMUX                                 (IOMUX_PINCM17)
#define GPIO_PWM_MOTOR1_C0_IOMUX_FUNC                IOMUX_PINCM17_PF_TIMA1_CCP0
#define GPIO_PWM_MOTOR1_C0_IDX                               DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_MOTOR1_C1_PORT                                            GPIOB
#define GPIO_PWM_MOTOR1_C1_PIN                                     DL_GPIO_PIN_1
#define GPIO_PWM_MOTOR1_C1_IOMUX                                 (IOMUX_PINCM13)
#define GPIO_PWM_MOTOR1_C1_IOMUX_FUNC                IOMUX_PINCM13_PF_TIMA1_CCP1
#define GPIO_PWM_MOTOR1_C1_IDX                               DL_TIMER_CC_1_INDEX

/* Defines for PWM_BUZZER */
#define PWM_BUZZER_INST                                                    TIMG0
#define PWM_BUZZER_INST_IRQHandler                              TIMG0_IRQHandler
#define PWM_BUZZER_INST_INT_IRQN                                (TIMG0_INT_IRQn)
#define PWM_BUZZER_INST_CLK_FREQ                                         5000000
/* GPIO defines for channel 1 */
#define GPIO_PWM_BUZZER_C1_PORT                                            GPIOA
#define GPIO_PWM_BUZZER_C1_PIN                                    DL_GPIO_PIN_13
#define GPIO_PWM_BUZZER_C1_IOMUX                                 (IOMUX_PINCM35)
#define GPIO_PWM_BUZZER_C1_IOMUX_FUNC                IOMUX_PINCM35_PF_TIMG0_CCP1
#define GPIO_PWM_BUZZER_C1_IDX                               DL_TIMER_CC_1_INDEX



/* Defines for TIMER_V */
#define TIMER_V_INST                                                     (TIMG6)
#define TIMER_V_INST_IRQHandler                                 TIMG6_IRQHandler
#define TIMER_V_INST_INT_IRQN                                   (TIMG6_INT_IRQn)
#define TIMER_V_INST_LOAD_VALUE                                          (9999U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                         DL_GPIO_PIN_1
#define GPIO_UART_0_TX_PIN                                         DL_GPIO_PIN_0
#define GPIO_UART_0_IOMUX_RX                                      (IOMUX_PINCM2)
#define GPIO_UART_0_IOMUX_TX                                      (IOMUX_PINCM1)
#define GPIO_UART_0_IOMUX_RX_FUNC                       IOMUX_PINCM2_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                       IOMUX_PINCM1_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_40_MHZ_9600_BAUD                                       (260)
#define UART_0_FBRD_40_MHZ_9600_BAUD                                        (27)




/* Defines for SPI_IMU */
#define SPI_IMU_INST                                                       SPI1
#define SPI_IMU_INST_IRQHandler                                 SPI1_IRQHandler
#define SPI_IMU_INST_INT_IRQN                                     SPI1_INT_IRQn
#define GPIO_SPI_IMU_PICO_PORT                                            GPIOB
#define GPIO_SPI_IMU_PICO_PIN                                     DL_GPIO_PIN_8
#define GPIO_SPI_IMU_IOMUX_PICO                                 (IOMUX_PINCM25)
#define GPIO_SPI_IMU_IOMUX_PICO_FUNC                 IOMUX_PINCM25_PF_SPI1_PICO
#define GPIO_SPI_IMU_POCI_PORT                                            GPIOB
#define GPIO_SPI_IMU_POCI_PIN                                    DL_GPIO_PIN_21
#define GPIO_SPI_IMU_IOMUX_POCI                                 (IOMUX_PINCM49)
#define GPIO_SPI_IMU_IOMUX_POCI_FUNC                 IOMUX_PINCM49_PF_SPI1_POCI
/* GPIO configuration for SPI_IMU */
#define GPIO_SPI_IMU_SCLK_PORT                                            GPIOA
#define GPIO_SPI_IMU_SCLK_PIN                                    DL_GPIO_PIN_17
#define GPIO_SPI_IMU_IOMUX_SCLK                                 (IOMUX_PINCM39)
#define GPIO_SPI_IMU_IOMUX_SCLK_FUNC                 IOMUX_PINCM39_PF_SPI1_SCLK
/* Defines for SPI_ENCODER */
#define SPI_ENCODER_INST                                                   SPI0
#define SPI_ENCODER_INST_IRQHandler                             SPI0_IRQHandler
#define SPI_ENCODER_INST_INT_IRQN                                 SPI0_INT_IRQn
#define GPIO_SPI_ENCODER_PICO_PORT                                        GPIOA
#define GPIO_SPI_ENCODER_PICO_PIN                                DL_GPIO_PIN_14
#define GPIO_SPI_ENCODER_IOMUX_PICO                             (IOMUX_PINCM36)
#define GPIO_SPI_ENCODER_IOMUX_PICO_FUNC             IOMUX_PINCM36_PF_SPI0_PICO
#define GPIO_SPI_ENCODER_POCI_PORT                                        GPIOB
#define GPIO_SPI_ENCODER_POCI_PIN                                DL_GPIO_PIN_19
#define GPIO_SPI_ENCODER_IOMUX_POCI                             (IOMUX_PINCM45)
#define GPIO_SPI_ENCODER_IOMUX_POCI_FUNC             IOMUX_PINCM45_PF_SPI0_POCI
/* GPIO configuration for SPI_ENCODER */
#define GPIO_SPI_ENCODER_SCLK_PORT                                        GPIOA
#define GPIO_SPI_ENCODER_SCLK_PIN                                DL_GPIO_PIN_12
#define GPIO_SPI_ENCODER_IOMUX_SCLK                             (IOMUX_PINCM34)
#define GPIO_SPI_ENCODER_IOMUX_SCLK_FUNC             IOMUX_PINCM34_PF_SPI0_SCLK



/* Defines for ADC_CCD */
#define ADC_CCD_INST                                                        ADC1
#define ADC_CCD_INST_IRQHandler                                  ADC1_IRQHandler
#define ADC_CCD_INST_INT_IRQN                                    (ADC1_INT_IRQn)
#define ADC_CCD_ADCMEM_0                                      DL_ADC12_MEM_IDX_0
#define ADC_CCD_ADCMEM_0_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC_CCD_ADCMEM_0_REF_VOLTAGE_V                                       3.3
#define ADC_CCD_INST_SUB_CH                                                  (1)
#define GPIO_ADC_CCD_C0_PORT                                               GPIOA
#define GPIO_ADC_CCD_C0_PIN                                       DL_GPIO_PIN_15

/* Defines for ADC_VIN */
#define ADC_VIN_INST                                                        ADC0
#define ADC_VIN_INST_IRQHandler                                  ADC0_IRQHandler
#define ADC_VIN_INST_INT_IRQN                                    (ADC0_INT_IRQn)
#define ADC_VIN_ADCMEM_1                                      DL_ADC12_MEM_IDX_1
#define ADC_VIN_ADCMEM_1_REF                     DL_ADC12_REFERENCE_VOLTAGE_VDDA
#define ADC_VIN_ADCMEM_1_REF_VOLTAGE_V                                       3.3
#define GPIO_ADC_VIN_C4_PORT                                               GPIOB
#define GPIO_ADC_VIN_C4_PIN                                       DL_GPIO_PIN_25



/* Defines for DMA_CH0 */
#define DMA_CH0_CHAN_ID                                                      (0)
#define ADC_CCD_INST_DMA_TRIGGER                      (DMA_ADC1_EVT_GEN_BD_TRIG)



/* Port definition for Pin Group GPIO_CCD */
#define GPIO_CCD_PORT                                                    (GPIOB)

/* Defines for PIN_SI: GPIOB.15 with pinCMx 32 on package pin 3 */
#define GPIO_CCD_PIN_SI_PIN                                     (DL_GPIO_PIN_15)
#define GPIO_CCD_PIN_SI_IOMUX                                    (IOMUX_PINCM32)
/* Port definition for Pin Group GPIO_SPI */
#define GPIO_SPI_PORT                                                    (GPIOB)

/* Defines for PIN_SPI_CS: GPIOB.18 with pinCMx 44 on package pin 15 */
#define GPIO_SPI_PIN_SPI_CS_PIN                                 (DL_GPIO_PIN_18)
#define GPIO_SPI_PIN_SPI_CS_IOMUX                                (IOMUX_PINCM44)
/* Port definition for Pin Group GPIO_SYS */
#define GPIO_SYS_PORT                                                    (GPIOB)

/* Defines for PIN_SYS: GPIOB.2 with pinCMx 15 on package pin 50 */
#define GPIO_SYS_PIN_SYS_PIN                                     (DL_GPIO_PIN_2)
#define GPIO_SYS_PIN_SYS_IOMUX                                   (IOMUX_PINCM15)
/* Port definition for Pin Group GPIO_LEDS */
#define GPIO_LEDS_PORT                                                   (GPIOB)

/* Defines for USER_LED_1: GPIOB.22 with pinCMx 50 on package pin 21 */
#define GPIO_LEDS_USER_LED_1_PIN                                (DL_GPIO_PIN_22)
#define GPIO_LEDS_USER_LED_1_IOMUX                               (IOMUX_PINCM50)
/* Defines for USER_LED_2: GPIOB.26 with pinCMx 57 on package pin 28 */
#define GPIO_LEDS_USER_LED_2_PIN                                (DL_GPIO_PIN_26)
#define GPIO_LEDS_USER_LED_2_IOMUX                               (IOMUX_PINCM57)
/* Defines for USER_LED_3: GPIOB.27 with pinCMx 58 on package pin 29 */
#define GPIO_LEDS_USER_LED_3_PIN                                (DL_GPIO_PIN_27)
#define GPIO_LEDS_USER_LED_3_IOMUX                               (IOMUX_PINCM58)
/* Port definition for Pin Group GPIO_ENCODER */
#define GPIO_ENCODER_PORT                                                (GPIOA)

/* Defines for SI_L: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GPIO_ENCODER_SI_L_PIN                                   (DL_GPIO_PIN_27)
#define GPIO_ENCODER_SI_L_IOMUX                                  (IOMUX_PINCM60)
/* Defines for SI_R: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_ENCODER_SI_R_PIN                                   (DL_GPIO_PIN_24)
#define GPIO_ENCODER_SI_R_IOMUX                                  (IOMUX_PINCM54)



/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_MOTOR0_init(void);
void SYSCFG_DL_TIM_CCD_init(void);
void SYSCFG_DL_PWM_MOTOR1_init(void);
void SYSCFG_DL_PWM_BUZZER_init(void);
void SYSCFG_DL_TIMER_V_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_IMU_init(void);
void SYSCFG_DL_SPI_ENCODER_init(void);
void SYSCFG_DL_ADC_CCD_init(void);
void SYSCFG_DL_ADC_VIN_init(void);
void SYSCFG_DL_DMA_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
