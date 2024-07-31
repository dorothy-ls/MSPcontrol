#include "task.h"
#include "hal.h"
#include "module.h"
#include "device.h"
#include "algorithm.h"

#define TEST
//#define TEST_MOTOR
//#define TEST_DELAY

#ifdef TEST_MOTOR

#define UART1_BUF_LEN 100
uint8_t uart1_rx_buf[UART1_BUF_LEN];
uint16_t uart1_rx_len = 0;
int uart1_state = 0;

Encoder left_encoder(&LEFT_CNT);
Encoder right_encoder(&RIGHT_CNT);
void LEFT_QEI_Handler();//���������TIM����ص�����ʵ��
void RIGHT_QEI_Handler();//���������TIM����ص�����ʵ��

N20_Motor left_motor(PWM_MOTOR_INST, GPIO_PWM_MOTOR_C0_IDX, GPIO_PWM_MOTOR_C1_IDX,
                     &left_encoder,
                     50 * 2 * 7,
                     33.4 / 2 / 1000 / 435 * 432,
                     0
                     );
N20_Motor right_motor(PWM_MOTOR_INST, GPIO_PWM_MOTOR_C2_IDX, GPIO_PWM_MOTOR_C3_IDX,
                     &right_encoder,
                     50 * 2 * 7,
                     33.4 / 2 / 1000 / 435 * 432,
                     0
);

Remote remote(UART_0_INST);
CCD ccd;

void setup()
{

    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);//�����жϳ�ʼ��
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    NVIC_EnableIRQ(TIM_ENCODE_INST_INT_IRQN);//��������������ʱ���ж�100k

    DL_Timer_startCounter(TIM_ENCODE_INST);//��������������ʱ������
    //DL_Timer_startCounter(PWM_MOTOR_INST);//��PWM��ʱ������
    right_motor.init();
    left_motor.init();
    ccd.init();

    register_LEFT_QEI_callback(LEFT_QEI_Handler);//ע�����QEI�ص�
    register_RIGHT_QEI_callback(RIGHT_QEI_Handler);//ע�����QEI�ص�

    DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);
}

void loop()
{
}

void task_handler()
{
    left_encoder.Handler();
    right_encoder.Handler();
    left_motor.Handler();
    right_motor.Handler();
    remote.Handler();
    ccd.Handler();
}

void LEFT_QEI_Handler()
{
    left_encoder.overflow_update();
}
void RIGHT_QEI_Handler()
{
    right_encoder.overflow_update();
}

uint32_t uart1_cnt = 0;
void UART_0_INST_IRQHandler(void)
{

    uart1_cnt++;
    uart1_rx_buf[uart1_rx_len] = DL_UART_Main_receiveData(UART_0_INST);
    uint8_t val = uart1_rx_buf[uart1_rx_len];
    uart1_rx_len++;
    if(uart1_rx_len >= UART1_BUF_LEN) uart1_rx_len = 0;
    //��⵽��β��־ʱ����
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

void TIM_CCD_INST_IRQHandler(void)
{
    ccd.SI_send();
}

#endif



//���Բ���ҵ���߼�
#ifdef TEST

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
volatile bool gCheckADC = false;
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

//��������
uint8_t start_flag[] = {0xfe, 0xfe};
uint8_t end_flag[] = {0xff, 0xff};
uint8_t temp_rx[128] = {0};
void setup()
{

    NVIC_EnableIRQ(TIM_CCD_INST_INT_IRQN);
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);//�����жϳ�ʼ��

    NVIC_EnableIRQ(ADC_CCD_INST_INT_IRQN);


//    NVIC_EnableIRQ(TIM_ENCODE_INST_INT_IRQN);//��������������ʱ���ж�100k
//
//    DL_Timer_startCounter(TIM_ENCODE_INST);//��������������ʱ������
    //DL_Timer_startCounter(PWM_MOTOR_INST);//��PWM��ʱ������
    
	ls7366r.init(MDR0_CONF,MDR1_CONF);

    right_motor.init();
    left_motor.init();

    ccd.init();




    //register_LEFT_QEI_callback(LEFT_QEI_Handler);//ע�����QEI�ص�
    //register_RIGHT_QEI_callback(RIGHT_QEI_Handler);//ע�����QEI�ص�

    DL_GPIO_setPins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);

//    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,(uint32_t) DL_ADC12_getMemResultAddress(ADC_CCD_INST,ADC_CCD_ADCMEM_0));
//    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t) ccd.data);
//    DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, 128);
    DL_DMA_disableChannel(DMA, DMA_CH0_CHAN_ID);
    //DL_ADC12_disableConversions(ADC_CCD_INST);
    NVIC_EnableIRQ(ADC_VIN_INST_INT_IRQN);//����ѹ���ADC�ж�
    delay_ms(1000);
    imu.init();
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
//    for(int i = 0;i< 128; i++)
//    {
//        temp_rx[i] = i;
//    }
//    UART_Transmit(UART_0_INST,temp_rx,128);
    //UART_Transmit(UART_0_INST, (uint8_t *)ccd.data, 128 * 2);

}

void loop()
{
//    DL_GPIO_togglePins(GPIO_LEDS_PORT,GPIO_LEDS_USER_LED_2_PIN);
//    delay_ms(500);
    if(ccd.sample_complete == true){
        UART_Transmit(UART_0_INST, start_flag, 2);
        UART_Transmit(UART_0_INST, (uint8_t *)ccd.data, 128 * 2);
        UART_Transmit(UART_0_INST, end_flag, 2);

        UART_Transmit(UART_0_INST, (uint8_t *)&chassis.x, 4);
        UART_Transmit(UART_0_INST, (uint8_t *)&chassis.y, 4);
        UART_Transmit(UART_0_INST, (uint8_t *)&chassis.ang, 4);
        UART_Transmit(UART_0_INST, (uint8_t *)&chassis.x_line, 4);
        UART_Transmit(UART_0_INST, (uint8_t *)&chassis.ang2, 4);
        UART_Transmit(UART_0_INST, end_flag, 2);
        UART_Transmit(UART_0_INST, temp_rx, 2);
        ccd.sample_complete = false;
    }
    test_power();
}

void task_handler()
{
    ls7366r.Handler();
	
    left_encoder.Handler();
    right_encoder.Handler();
    left_motor.Handler();
    right_motor.Handler();
    remote.Handler();
    ccd.Handler();
    imu.Handler();
    signal_Handler();


    chassis.Handler();


    controller.Handler();
    pid_controller.Handler();


#ifdef USE_REMOTE //ң����
    switch (remote.mode) {
        case 0: { //ֹͣ
            chassis.state = CHASSIS_STOP;
        }break;
        case 1: { //ң��
//            float thresh = 0;
//            if(remote.vertical < thresh && remote.vertical > -thresh){
//                chassis.v_set = 0;
//            }else chassis.v_set = remote.vertical * 0.1;
//            if(remote.vertical < thresh && remote.vertical > -thresh){
//                chassis.w_set = 0;
//            }else chassis.w_set = remote.horizontal * (-0.1);
//            chassis.state = CHASSIS_RUN;
        }break;
        case 2: { //λ�ÿ��������Ծ���
//            const float l = 0.3;
//            static float x_array[] = {0, l, l, 0};
//            static float y_array[] = {0, 0, -l, -l};
//            static int array_len = 4, index = 0;
//
//            controller.x_set = 0.96;
////          if(controller.reached == true){
////              if(++index >= array_len) index = 0;
////              controller.x_set = x_array[index];
////              controller.y_set = y_array[index];
////              controller.reached = false;
////          }
//            controller.state = 1;
//            chassis.state = CHASSIS_RUN;
            chassis.w_set = 0.02;
            chassis.state = CHASSIS_RUN;
        } break;
        case 3: {
//            controller.x_set = remote.x;
//            controller.y_set = remote.y;
//            chassis.state = CHASSIS_RUN;


        }break;
    }
#else

#endif

}

uint32_t uart1_cnt = 0;
void UART_0_INST_IRQHandler(void)
{
    uart1_cnt++;
    uart1_rx_buf[uart1_rx_len] = DL_UART_Main_receiveData(UART_0_INST);
    uint8_t val = uart1_rx_buf[uart1_rx_len];
    uart1_rx_len++;
    if(uart1_rx_len >= UART1_BUF_LEN) uart1_rx_len = 0;
    //��⵽��β��־ʱ����
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
    ccd.SI_send();
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
    DL_ADC12_enableConversions(ADC_VIN_INST);
    DL_ADC12_startConversion(ADC_VIN_INST);
    while (false == gCheckADC);
    power_vin = DL_ADC12_getMemResult(ADC_VIN_INST,  DL_ADC12_MEM_IDX_1);
    gCheckADC = false;
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

}
uint32_t ADC_VIN_cnt = 0;
void ADC_VIN_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC_VIN_INST)) {
        case DL_ADC12_IIDX_MEM1_RESULT_LOADED:
            gCheckADC = true;
            ADC_VIN_cnt ++;

            break;
        default:
            break;
    }
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



#endif


