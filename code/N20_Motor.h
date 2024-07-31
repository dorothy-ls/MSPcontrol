#ifndef CONTROL_N20_MOTOR_H
#define CONTROL_N20_MOTOR_H

#define PWM_DUTY_MAX 5000//ռ�ձ����ֵ��ARR)

#include "hal.h"
#include "Encoder.h"
#include "Motor.h"
#include "config.h"

class N20_Motor: public Motor{
public:
    Encoder* encoder;//ÿһ��motor��Ӧһ��encoder
    float reduction_rate;//������ٱ�
    float radius;

    N20_Motor(GPTIMER_Regs *htim, DL_TIMER_CC_INDEX pwm_channel1, DL_TIMER_CC_INDEX pwm_channel2,
                  Encoder* encoder,
                  float reduction_rate, float radius);
    void init();
    void Handler();//systick�жϺ���

private:
    GPTIMER_Regs * htim;
    DL_TIMER_CC_INDEX pwm_channel1;//һ��motor��Ӧ����pwmͨ�� ����GPIO_PWM_MOTOR_C0_IDX
    DL_TIMER_CC_INDEX pwm_channel2;

    int32_t inc_pulse = 0;


    void pwm_set_duty(DL_TIMER_CC_INDEX channel, uint16_t duty);//����pwmռ�ձ�
    void measure_parameter();
    void output_intensity();

};


#endif
