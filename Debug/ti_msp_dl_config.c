/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gPWM_MOTOR0Backup;
DL_TimerA_backupConfig gPWM_MOTOR1Backup;
DL_TimerG_backupConfig gTIMER_VBackup;
DL_SPI_backupConfig gSPI_IMUBackup;
DL_SPI_backupConfig gSPI_ENCODERBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_PWM_MOTOR0_init();
    SYSCFG_DL_TIM_CCD_init();
    SYSCFG_DL_PWM_MOTOR1_init();
    SYSCFG_DL_PWM_BUZZER_init();
    SYSCFG_DL_TIMER_V_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_SPI_IMU_init();
    SYSCFG_DL_SPI_ENCODER_init();
    SYSCFG_DL_ADC_CCD_init();
    SYSCFG_DL_ADC_VIN_init();
    SYSCFG_DL_DMA_init();
    SYSCFG_DL_SYSTICK_init();
    /* Ensure backup structures have no valid state */
	gPWM_MOTOR0Backup.backupRdy 	= false;
	gPWM_MOTOR1Backup.backupRdy 	= false;
	gTIMER_VBackup.backupRdy 	= false;

	gSPI_IMUBackup.backupRdy 	= false;
	gSPI_ENCODERBackup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(PWM_MOTOR0_INST, &gPWM_MOTOR0Backup);
	retStatus &= DL_TimerA_saveConfiguration(PWM_MOTOR1_INST, &gPWM_MOTOR1Backup);
	retStatus &= DL_TimerG_saveConfiguration(TIMER_V_INST, &gTIMER_VBackup);
	retStatus &= DL_SPI_saveConfiguration(SPI_IMU_INST, &gSPI_IMUBackup);
	retStatus &= DL_SPI_saveConfiguration(SPI_ENCODER_INST, &gSPI_ENCODERBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(PWM_MOTOR0_INST, &gPWM_MOTOR0Backup, false);
	retStatus &= DL_TimerA_restoreConfiguration(PWM_MOTOR1_INST, &gPWM_MOTOR1Backup, false);
	retStatus &= DL_TimerG_restoreConfiguration(TIMER_V_INST, &gTIMER_VBackup, false);
	retStatus &= DL_SPI_restoreConfiguration(SPI_IMU_INST, &gSPI_IMUBackup);
	retStatus &= DL_SPI_restoreConfiguration(SPI_ENCODER_INST, &gSPI_ENCODERBackup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(PWM_MOTOR0_INST);
    DL_TimerG_reset(TIM_CCD_INST);
    DL_TimerA_reset(PWM_MOTOR1_INST);
    DL_TimerG_reset(PWM_BUZZER_INST);
    DL_TimerG_reset(TIMER_V_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_SPI_reset(SPI_IMU_INST);
    DL_SPI_reset(SPI_ENCODER_INST);
    DL_ADC12_reset(ADC_CCD_INST);
    DL_ADC12_reset(ADC_VIN_INST);



    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(PWM_MOTOR0_INST);
    DL_TimerG_enablePower(TIM_CCD_INST);
    DL_TimerA_enablePower(PWM_MOTOR1_INST);
    DL_TimerG_enablePower(PWM_BUZZER_INST);
    DL_TimerG_enablePower(TIMER_V_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_SPI_enablePower(SPI_IMU_INST);
    DL_SPI_enablePower(SPI_ENCODER_INST);
    DL_ADC12_enablePower(ADC_CCD_INST);
    DL_ADC12_enablePower(ADC_VIN_INST);


    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXIN_IOMUX);
    DL_GPIO_initPeripheralAnalogFunction(GPIO_HFXOUT_IOMUX);

    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_MOTOR0_C2_IOMUX,GPIO_PWM_MOTOR0_C2_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_MOTOR0_C2_PORT, GPIO_PWM_MOTOR0_C2_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_MOTOR0_C3_IOMUX,GPIO_PWM_MOTOR0_C3_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_MOTOR0_C3_PORT, GPIO_PWM_MOTOR0_C3_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_TIM_CCD_C1_IOMUX,GPIO_TIM_CCD_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_TIM_CCD_C1_PORT, GPIO_TIM_CCD_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_MOTOR1_C0_IOMUX,GPIO_PWM_MOTOR1_C0_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_MOTOR1_C0_PORT, GPIO_PWM_MOTOR1_C0_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_MOTOR1_C1_IOMUX,GPIO_PWM_MOTOR1_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_MOTOR1_C1_PORT, GPIO_PWM_MOTOR1_C1_PIN);
    DL_GPIO_initPeripheralOutputFunction(GPIO_PWM_BUZZER_C1_IOMUX,GPIO_PWM_BUZZER_C1_IOMUX_FUNC);
    DL_GPIO_enableOutput(GPIO_PWM_BUZZER_C1_PORT, GPIO_PWM_BUZZER_C1_PIN);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_IMU_IOMUX_SCLK, GPIO_SPI_IMU_IOMUX_SCLK_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_IMU_IOMUX_PICO, GPIO_SPI_IMU_IOMUX_PICO_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_SPI_IMU_IOMUX_POCI, GPIO_SPI_IMU_IOMUX_POCI_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_ENCODER_IOMUX_SCLK, GPIO_SPI_ENCODER_IOMUX_SCLK_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_SPI_ENCODER_IOMUX_PICO, GPIO_SPI_ENCODER_IOMUX_PICO_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_SPI_ENCODER_IOMUX_POCI, GPIO_SPI_ENCODER_IOMUX_POCI_FUNC);

    DL_GPIO_initDigitalOutput(GPIO_CCD_PIN_SI_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_SPI_PIN_SPI_CS_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_SYS_PIN_SYS_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_LEDS_USER_LED_1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_LEDS_USER_LED_2_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_LEDS_USER_LED_3_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_ENCODER_SI_L_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_ENCODER_SI_R_IOMUX);

    DL_GPIO_setPins(GPIO_ENCODER_PORT, GPIO_ENCODER_SI_L_PIN |
		GPIO_ENCODER_SI_R_PIN);
    DL_GPIO_enableOutput(GPIO_ENCODER_PORT, GPIO_ENCODER_SI_L_PIN |
		GPIO_ENCODER_SI_R_PIN);
    DL_GPIO_clearPins(GPIOB, GPIO_CCD_PIN_SI_PIN |
		GPIO_SYS_PIN_SYS_PIN |
		GPIO_LEDS_USER_LED_1_PIN |
		GPIO_LEDS_USER_LED_2_PIN |
		GPIO_LEDS_USER_LED_3_PIN);
    DL_GPIO_setPins(GPIOB, GPIO_SPI_PIN_SPI_CS_PIN);
    DL_GPIO_enableOutput(GPIOB, GPIO_CCD_PIN_SI_PIN |
		GPIO_SPI_PIN_SPI_CS_PIN |
		GPIO_SYS_PIN_SYS_PIN |
		GPIO_LEDS_USER_LED_1_PIN |
		GPIO_LEDS_USER_LED_2_PIN |
		GPIO_LEDS_USER_LED_3_PIN);

}


static const DL_SYSCTL_SYSPLLConfig gSYSPLLConfig = {
    .inputFreq              = DL_SYSCTL_SYSPLL_INPUT_FREQ_16_32_MHZ,
	.rDivClk2x              = 1,
	.rDivClk1               = 0,
	.rDivClk0               = 0,
	.enableCLK2x            = DL_SYSCTL_SYSPLL_CLK2X_DISABLE,
	.enableCLK1             = DL_SYSCTL_SYSPLL_CLK1_DISABLE,
	.enableCLK0             = DL_SYSCTL_SYSPLL_CLK0_ENABLE,
	.sysPLLMCLK             = DL_SYSCTL_SYSPLL_MCLK_CLK0,
	.sysPLLRef              = DL_SYSCTL_SYSPLL_REF_HFCLK,
	.qDiv                   = 7,
	.pDiv                   = DL_SYSCTL_SYSPLL_PDIV_2
};
SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);
    DL_SYSCTL_setFlashWaitState(DL_SYSCTL_FLASH_WAIT_STATE_2);

    
	DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
	/* Set default configuration */
	DL_SYSCTL_disableHFXT();
	DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_setHFCLKSourceHFXTParams(DL_SYSCTL_HFXT_RANGE_32_48_MHZ,0, false);
    DL_SYSCTL_configSYSPLL((DL_SYSCTL_SYSPLLConfig *) &gSYSPLLConfig);
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_2);
    DL_SYSCTL_setMCLKSource(SYSOSC, HSCLK, DL_SYSCTL_HSCLK_SOURCE_SYSPLL);

}


/*
 * Timer clock configuration to be sourced by  / 1 (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   80000000 Hz = 80000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gPWM_MOTOR0ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gPWM_MOTOR0Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 5000,
    .isTimerWithFourCC = true,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_MOTOR0_init(void) {

    DL_TimerA_setClockConfig(
        PWM_MOTOR0_INST, (DL_TimerA_ClockConfig *) &gPWM_MOTOR0ClockConfig);

    DL_TimerA_initPWMMode(
        PWM_MOTOR0_INST, (DL_TimerA_PWMConfig *) &gPWM_MOTOR0Config);

    DL_TimerA_setCaptureCompareOutCtl(PWM_MOTOR0_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_2_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_MOTOR0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_2_INDEX);
    DL_TimerA_setCaptureCompareValue(PWM_MOTOR0_INST, 5000, DL_TIMER_CC_2_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(PWM_MOTOR0_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_3_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_MOTOR0_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_3_INDEX);
    DL_TimerA_setCaptureCompareValue(PWM_MOTOR0_INST, 5000, DL_TIMER_CC_3_INDEX);

    DL_TimerA_enableClock(PWM_MOTOR0_INST);


    
    DL_TimerA_setCCPDirection(PWM_MOTOR0_INST , DL_TIMER_CC2_OUTPUT | DL_TIMER_CC3_OUTPUT );


}
/*
 * Timer clock configuration to be sourced by  / 1 (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   80000000 Hz = 80000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gTIM_CCDClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gTIM_CCDConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 640,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIM_CCD_init(void) {

    DL_TimerG_setClockConfig(
        TIM_CCD_INST, (DL_TimerG_ClockConfig *) &gTIM_CCDClockConfig);

    DL_TimerG_initPWMMode(
        TIM_CCD_INST, (DL_TimerG_PWMConfig *) &gTIM_CCDConfig);

    DL_TimerG_setCaptureCompareOutCtl(TIM_CCD_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(TIM_CCD_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(TIM_CCD_INST, 320, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(TIM_CCD_INST);
    DL_TimerG_enableEvent(TIM_CCD_INST, DL_TIMERG_EVENT_ROUTE_1, (DL_TIMERG_EVENT_CC0_UP_EVENT));

    DL_TimerG_setPublisherChanID(TIM_CCD_INST, DL_TIMERG_PUBLISHER_INDEX_0, TIM_CCD_INST_PUB_0_CH);


    DL_TimerG_enableInterrupt(TIM_CCD_INST , DL_TIMER_INTERRUPT_CC1_UP_EVENT);

    NVIC_SetPriority(TIM_CCD_INST_INT_IRQN, 1);
    DL_TimerG_setCCPDirection(TIM_CCD_INST , DL_TIMER_CC1_OUTPUT );


}
/*
 * Timer clock configuration to be sourced by  / 1 (80000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   80000000 Hz = 80000000 Hz / (1 * (0 + 1))
 */
static const DL_TimerA_ClockConfig gPWM_MOTOR1ClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_1,
    .prescale = 0U
};

static const DL_TimerA_PWMConfig gPWM_MOTOR1Config = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 5000,
    .isTimerWithFourCC = true,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_MOTOR1_init(void) {

    DL_TimerA_setClockConfig(
        PWM_MOTOR1_INST, (DL_TimerA_ClockConfig *) &gPWM_MOTOR1ClockConfig);

    DL_TimerA_initPWMMode(
        PWM_MOTOR1_INST, (DL_TimerA_PWMConfig *) &gPWM_MOTOR1Config);

    DL_TimerA_setCaptureCompareOutCtl(PWM_MOTOR1_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_0_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_MOTOR1_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_0_INDEX);
    DL_TimerA_setCaptureCompareValue(PWM_MOTOR1_INST, 5000, DL_TIMER_CC_0_INDEX);

    DL_TimerA_setCaptureCompareOutCtl(PWM_MOTOR1_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERA_CAPTURE_COMPARE_1_INDEX);

    DL_TimerA_setCaptCompUpdateMethod(PWM_MOTOR1_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERA_CAPTURE_COMPARE_1_INDEX);
    DL_TimerA_setCaptureCompareValue(PWM_MOTOR1_INST, 5000, DL_TIMER_CC_1_INDEX);

    DL_TimerA_enableClock(PWM_MOTOR1_INST);


    
    DL_TimerA_setCCPDirection(PWM_MOTOR1_INST , DL_TIMER_CC0_OUTPUT | DL_TIMER_CC1_OUTPUT );


}
/*
 * Timer clock configuration to be sourced by  / 8 (5000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   5000000 Hz = 5000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gPWM_BUZZERClockConfig = {
    .clockSel = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale = 0U
};

static const DL_TimerG_PWMConfig gPWM_BUZZERConfig = {
    .pwmMode = DL_TIMER_PWM_MODE_EDGE_ALIGN_UP,
    .period = 5000,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_PWM_BUZZER_init(void) {

    DL_TimerG_setClockConfig(
        PWM_BUZZER_INST, (DL_TimerG_ClockConfig *) &gPWM_BUZZERClockConfig);

    DL_TimerG_initPWMMode(
        PWM_BUZZER_INST, (DL_TimerG_PWMConfig *) &gPWM_BUZZERConfig);

    DL_TimerG_setCaptureCompareOutCtl(PWM_BUZZER_INST, DL_TIMER_CC_OCTL_INIT_VAL_LOW,
		DL_TIMER_CC_OCTL_INV_OUT_DISABLED, DL_TIMER_CC_OCTL_SRC_FUNCVAL,
		DL_TIMERG_CAPTURE_COMPARE_1_INDEX);

    DL_TimerG_setCaptCompUpdateMethod(PWM_BUZZER_INST, DL_TIMER_CC_UPDATE_METHOD_IMMEDIATE, DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
    DL_TimerG_setCaptureCompareValue(PWM_BUZZER_INST, 2500, DL_TIMER_CC_1_INDEX);

    DL_TimerG_enableClock(PWM_BUZZER_INST);


    
    DL_TimerG_setCCPDirection(PWM_BUZZER_INST , DL_TIMER_CC1_OUTPUT );


}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (10000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   10000000 Hz = 10000000 Hz / (8 * (0 + 1))
 */
static const DL_TimerG_ClockConfig gTIMER_VClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 0U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_V_INST_LOAD_VALUE = (1ms * 10000000 Hz) - 1
 */
static const DL_TimerG_TimerConfig gTIMER_VTimerConfig = {
    .period     = TIMER_V_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_V_init(void) {

    DL_TimerG_setClockConfig(TIMER_V_INST,
        (DL_TimerG_ClockConfig *) &gTIMER_VClockConfig);

    DL_TimerG_initTimerMode(TIMER_V_INST,
        (DL_TimerG_TimerConfig *) &gTIMER_VTimerConfig);
    DL_TimerG_enableInterrupt(TIMER_V_INST , DL_TIMERG_INTERRUPT_ZERO_EVENT);
	NVIC_SetPriority(TIMER_V_INST_INT_IRQN, 1);
    DL_TimerG_enableClock(TIMER_V_INST);





}



static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 9600
     *  Actual baud rate: 9599.81
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_40_MHZ_9600_BAUD, UART_0_FBRD_40_MHZ_9600_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);
    /* Setting the Interrupt Priority */
    NVIC_SetPriority(UART_0_INST_INT_IRQN, 2);


    DL_UART_Main_enable(UART_0_INST);
}

static const DL_SPI_Config gSPI_IMU_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO3_POL0_PHA0,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_8,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
};

static const DL_SPI_ClockConfig gSPI_IMU_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_SPI_IMU_init(void) {
    DL_SPI_setClockConfig(SPI_IMU_INST, (DL_SPI_ClockConfig *) &gSPI_IMU_clockConfig);

    DL_SPI_init(SPI_IMU_INST, (DL_SPI_Config *) &gSPI_IMU_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     4000000 = (80000000)/((1 + 9) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(SPI_IMU_INST, 9);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(SPI_IMU_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(SPI_IMU_INST);
}
static const DL_SPI_Config gSPI_ENCODER_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO3_POL0_PHA0,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_8,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
};

static const DL_SPI_ClockConfig gSPI_ENCODER_clockConfig = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

SYSCONFIG_WEAK void SYSCFG_DL_SPI_ENCODER_init(void) {
    DL_SPI_setClockConfig(SPI_ENCODER_INST, (DL_SPI_ClockConfig *) &gSPI_ENCODER_clockConfig);

    DL_SPI_init(SPI_ENCODER_INST, (DL_SPI_Config *) &gSPI_ENCODER_config);

    /* Configure Controller mode */
    /*
     * Set the bit rate clock divider to generate the serial output clock
     *     outputBitRate = (spiInputClock) / ((1 + SCR) * 2)
     *     4000000 = (80000000)/((1 + 9) * 2)
     */
    DL_SPI_setBitRateSerialClockDivider(SPI_ENCODER_INST, 9);
    /* Set RX and TX FIFO threshold levels */
    DL_SPI_setFIFOThreshold(SPI_ENCODER_INST, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);

    /* Enable module */
    DL_SPI_enable(SPI_ENCODER_INST);
}

/* ADC_CCD Initialization */
static const DL_ADC12_ClockConfig gADC_CCDClockConfig = {
    .clockSel       = DL_ADC12_CLOCK_SYSOSC,
    .divideRatio    = DL_ADC12_CLOCK_DIVIDE_1,
    .freqRange      = DL_ADC12_CLOCK_FREQ_RANGE_24_TO_32,
};
SYSCONFIG_WEAK void SYSCFG_DL_ADC_CCD_init(void)
{
    DL_ADC12_setClockConfig(ADC_CCD_INST, (DL_ADC12_ClockConfig *) &gADC_CCDClockConfig);
    DL_ADC12_initSingleSample(ADC_CCD_INST,
        DL_ADC12_REPEAT_MODE_ENABLED, DL_ADC12_SAMPLING_SOURCE_AUTO, DL_ADC12_TRIG_SRC_EVENT,
        DL_ADC12_SAMP_CONV_RES_12_BIT, DL_ADC12_SAMP_CONV_DATA_FORMAT_UNSIGNED);
    DL_ADC12_configConversionMem(ADC_CCD_INST, ADC_CCD_ADCMEM_0,
        DL_ADC12_INPUT_CHAN_0, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_DISABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_TRIGGER_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_setPowerDownMode(ADC_CCD_INST,DL_ADC12_POWER_DOWN_MODE_MANUAL);
    DL_ADC12_setSampleTime0(ADC_CCD_INST,2);
    DL_ADC12_enableDMA(ADC_CCD_INST);
    DL_ADC12_setDMASamplesCnt(ADC_CCD_INST,1);
    DL_ADC12_enableDMATrigger(ADC_CCD_INST,(DL_ADC12_DMA_MEM0_RESULT_LOADED));
    DL_ADC12_setSubscriberChanID(ADC_CCD_INST,ADC_CCD_INST_SUB_CH);
    /* Enable ADC12 interrupt */
    DL_ADC12_clearInterruptStatus(ADC_CCD_INST,(DL_ADC12_INTERRUPT_DMA_DONE));
    DL_ADC12_enableInterrupt(ADC_CCD_INST,(DL_ADC12_INTERRUPT_DMA_DONE));
    NVIC_SetPriority(ADC_CCD_INST_INT_IRQN, 1);
    DL_ADC12_enableConversions(ADC_CCD_INST);
}
/* ADC_VIN Initialization */
static const DL_ADC12_ClockConfig gADC_VINClockConfig = {
    .clockSel       = DL_ADC12_CLOCK_SYSOSC,
    .divideRatio    = DL_ADC12_CLOCK_DIVIDE_1,
    .freqRange      = DL_ADC12_CLOCK_FREQ_RANGE_24_TO_32,
};
SYSCONFIG_WEAK void SYSCFG_DL_ADC_VIN_init(void)
{
    DL_ADC12_setClockConfig(ADC_VIN_INST, (DL_ADC12_ClockConfig *) &gADC_VINClockConfig);
    DL_ADC12_setStartAddress(ADC_VIN_INST, DL_ADC12_SEQ_START_ADDR_01);
    DL_ADC12_configConversionMem(ADC_VIN_INST, ADC_VIN_ADCMEM_1,
        DL_ADC12_INPUT_CHAN_4, DL_ADC12_REFERENCE_VOLTAGE_VDDA, DL_ADC12_SAMPLE_TIMER_SOURCE_SCOMP0, DL_ADC12_AVERAGING_MODE_DISABLED,
        DL_ADC12_BURN_OUT_SOURCE_DISABLED, DL_ADC12_TRIGGER_MODE_AUTO_NEXT, DL_ADC12_WINDOWS_COMP_MODE_DISABLED);
    DL_ADC12_setPowerDownMode(ADC_VIN_INST,DL_ADC12_POWER_DOWN_MODE_MANUAL);
    DL_ADC12_setSampleTime0(ADC_VIN_INST,2);
    /* Enable ADC12 interrupt */
    DL_ADC12_clearInterruptStatus(ADC_VIN_INST,(DL_ADC12_INTERRUPT_MEM1_RESULT_LOADED));
    DL_ADC12_enableInterrupt(ADC_VIN_INST,(DL_ADC12_INTERRUPT_MEM1_RESULT_LOADED));
    DL_ADC12_enableConversions(ADC_VIN_INST);
}

static const DL_DMA_Config gDMA_CH0Config = {
    .transferMode   = DL_DMA_SINGLE_TRANSFER_MODE,
    .extendedMode   = DL_DMA_NORMAL_MODE,
    .destIncrement  = DL_DMA_ADDR_INCREMENT,
    .srcIncrement   = DL_DMA_ADDR_UNCHANGED,
    .destWidth      = DL_DMA_WIDTH_HALF_WORD,
    .srcWidth       = DL_DMA_WIDTH_HALF_WORD,
    .trigger        = ADC_CCD_INST_DMA_TRIGGER,
    .triggerType    = DL_DMA_TRIGGER_TYPE_EXTERNAL,
};

SYSCONFIG_WEAK void SYSCFG_DL_DMA_CH0_init(void)
{
    DL_DMA_initChannel(DMA, DMA_CH0_CHAN_ID , (DL_DMA_Config *) &gDMA_CH0Config);
}
SYSCONFIG_WEAK void SYSCFG_DL_DMA_init(void){
    SYSCFG_DL_DMA_CH0_init();
}


SYSCONFIG_WEAK void SYSCFG_DL_SYSTICK_init(void)
{
    /*
     * Initializes the SysTick period to 1.00 ms,
     * enables the interrupt, and starts the SysTick Timer
     */
    DL_SYSTICK_config(80000);
}

