#ifndef CONTROL_N20_MOTOR_H
#define CONTROL_N20_MOTOR_H

#define PWM_DUTY_MAX 5000//占空比最大值（ARR)

#include "ti_msp_dl_config.h"
#include "Encoder.h"
#include "Motor.h"
#include "config.h"

class N20_Motor: public Motor{
public:
    Encoder* encoder;//每一个motor对应一个encoder
    float reduction_rate;//电机减速比
    float radius;
    float deadzone;
    N20_Motor(GPTIMER_Regs *htim, DL_TIMER_CC_INDEX pwm_channel1, DL_TIMER_CC_INDEX pwm_channel2,
                  Encoder* encoder,
                  float reduction_rate, float radius, float deadzone);
    void init();
    void Handler();//systick中断函数

private:
    GPTIMER_Regs * htim;
    DL_TIMER_CC_INDEX pwm_channel1;//一个motor对应两个pwm通道 例：GPIO_PWM_MOTOR_C0_IDX
    DL_TIMER_CC_INDEX pwm_channel2;

    int32_t inc_pulse = 0;


    void pwm_set_duty(DL_TIMER_CC_INDEX channel, uint16_t duty);//设置pwm占空比
    void measure_parameter();
    void output_intensity();

};


#endif
