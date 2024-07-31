#include "task.h"
#include "hal.h"
#include "module.h"
#include "device.h"
#include "algorithm.h"

#define USE_REMOTE

#define UART1_BUF_LEN 100
#define v_th 9
uint8_t uart1_rx_buf[UART1_BUF_LEN];
uint16_t uart1_rx_len = 0;
int uart1_state = 0;
volatile uint32_t gpioA;
volatile uint32_t gpioB;
volatile uint16_t power_vin = 0;
volatile float vin = 12;
volatile uint8_t signal_en_flag = 0;

LS7366R ls7366r(SPI_ENCODER_INST,GPIO_ENCODER_PORT,GPIO_ENCODER_SI_L_PIN,GPIO_ENCODER_SI_R_PIN);
Encoder left_encoder(&(ls7366r.leftValue));
Encoder right_encoder(&(ls7366r.rightValue));

void test_power();

void signal_start();
void signal_Handler();


N20_Motor right_motor(PWM_MOTOR0_INST, GPIO_PWM_MOTOR0_C3_IDX, GPIO_PWM_MOTOR0_C2_IDX,
                     &right_encoder,
                     150 * 4 * 7,
                     33.4 / 2 / 1000 / 435 * 432
);
N20_Motor left_motor(PWM_MOTOR1_INST, GPIO_PWM_MOTOR1_C0_IDX, GPIO_PWM_MOTOR1_C1_IDX,
                     &left_encoder,
                     150 * 4 * 7,
                     33.4 / 2 / 1000 / 435 * 432
                     );
CCD ccd;
Remote remote(UART_0_INST);
IMU imu;
Buzzer buzzer(PWM_BUZZER_INST);

Chassis chassis(&left_motor, &right_motor, &imu, &ccd, 112.5 / 1000);
Controller controller(&chassis);
PID_Controller pid_controller(&chassis);

uint8_t start_flag[] = {0xfe, 0xfe};
uint8_t end_flag[] = {0xff, 0xff};
uint8_t temp_rx[128] = {0};

bool car_start = false;
void setup()
{ 
	ls7366r.init(MDR0_CONF,MDR1_CONF);

    right_motor.init();
    left_motor.init();

    ccd.init();

    delay_ms(1000);
    //imu.init();


    car_start = true;
}

void loop()
{
    if(ccd.sample_complete == true){
		HAL_UART_Transmit(huart1, start_flag, 2, 0xffff);
		HAL_UART_Transmit(huart1, (uint8_t *)ccd.data, 128 * 2, 0xffff);
		HAL_UART_Transmit(huart1, end_flag, 2, 0xffff);

		HAL_UART_Transmit(huart1, (uint8_t *)&chassis.x, 4, 0xffff);
		HAL_UART_Transmit(huart1, (uint8_t *)&chassis.y, 4, 0xffff);
		HAL_UART_Transmit(huart1, (uint8_t *)&chassis.ang, 4, 0xffff);
		HAL_UART_Transmit(huart1, (uint8_t *)&chassis.x_line, 4, 0xffff);
		HAL_UART_Transmit(huart1, (uint8_t *)&chassis.y_line, 4, 0xffff);
		HAL_UART_Transmit(huart1, end_flag, 2, 0xffff);
        ccd.sample_complete = false;
    }
}

void task_handler()
{
    if(car_start){
        ls7366r.Handler();

        left_encoder.Handler();
        right_encoder.Handler();
        left_motor.Handler();
        right_motor.Handler();
        remote.Handler();
        ccd.Handler();
        //imu.Handler();

        chassis.Handler();


        controller.Handler();
        pid_controller.Handler();
    }

	test_power();


}

uint32_t uart1_cnt = 0;
void UART_0_INST_IRQHandler(void)
{
    uart1_cnt++;
    uart1_rx_buf[uart1_rx_len] = DL_UART_Main_receiveData(UART_0_INST);
    uint8_t val = uart1_rx_buf[uart1_rx_len];
    uart1_rx_len++;
    if(uart1_rx_len >= UART1_BUF_LEN) uart1_rx_len = 0;
    
    if(val == '\r')
    {
        uart1_state = 1;
    }
    else if(val == '\n')
    {
        if(uart1_state == 1)
        {
            memcpy(remote.data, uart1_rx_buf, uart1_rx_len);
            remote.len = uart1_rx_len;
            uart1_state = 0;
            uart1_rx_len = 0;
        }else uart1_state = 0;
    }

}
uint32_t CCD_cnt = 0;
void TIM_CCD_INST_IRQHandler(void)
{
    CCD_cnt ++;
    //ccd.SI_send();
}

uint32_t ADC_cnt = 0;
void ADC_CCD_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC_CCD_INST)) {
            case DL_ADC12_IIDX_DMA_DONE:
                DL_DMA_disableChannel(DMA, DMA_CH0_CHAN_ID);
                DL_ADC12_disableConversions(ADC_CCD_INST);
                ccd.sample_complete = true;
                chassis.process();
                ADC_cnt++;
                break;
            default:
                break;
        }
//    ccd.sample_complete = true;
//    DL_DMA_disableChannel(DMA, DMA_CH0_CHAN_ID);
//    DL_ADC12_disableConversions(ADC_CCD_INST);
    //DL_ADC12_clearInterruptStatus(ADC_CCD_INST,DL_ADC12_IIDX_DMA_DONE);
}


void test_power()
{
    static uint8_t power_flag = 0;
    power_vin = DL_ADC12_getMemResult(ADC_VIN_INST,  DL_ADC12_MEM_IDX_1);
    vin = float((float)power_vin/1890)*12;
    if(vin <= v_th && vin >=7 )
    {
        power_flag = 1;
        buzzer.start();
    }
    else if(power_flag == 1)
        {
        buzzer.stop();
        power_flag = 0;
        }
    DL_ADC12_enableConversions(ADC_VIN_INST);
    DL_ADC12_startConversion(ADC_VIN_INST);
}


//void signal_start()
//{
//    signal_en_flag = 1;
//    buzzer.start();
//    DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_3_PIN);
//}

void signal_Handler()
{
    static uint32_t temp_utick = 0;
    if(signal_en_flag == 1)
    {
        temp_utick = utick;
        signal_en_flag = 0;
        buzzer.start();
        DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_3_PIN);
    }
    if(utick > temp_utick + 1000)
    {
        buzzer.stop();
        DL_GPIO_clearPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_3_PIN);
        temp_utick = 0;
    }
}



