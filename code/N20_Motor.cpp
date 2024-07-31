#include "N20_Motor.h"

void N20_Motor::Handler() //systick IRQ
{
    measure_parameter();//1ms获取一次反馈数据
    output_intensity();//1ms进行一次输出
}

void N20_Motor::measure_parameter()//获取当前车轮线速度和角度
{
    float inc = -(float)encoder->pulse / this->reduction_rate * 360;//脉冲数量转化为角度（degree）
    inc_pulse = encoder->pulse;
    encoder->pulse = 0;//读取一次encoder的pulse，随后清零，减小累计误差
    this->v = inc / 180 * M_PI * MAIN_LOOP_FREQ * radius;//角速度转化为线速度
    this->ang += inc;
    if(this->ang >= 360){
        this->ang -= (int)(this->ang / 360) * 360;
    }else if(this->ang < 0){
        this->ang -= (int)(this->ang / 360) * 360 - 360;
    }//保持角度在0-360
}



void N20_Motor::pwm_set_duty(DL_TIMER_CC_INDEX channel, uint16_t duty)
{ //0-5000 TODO cube配置
    DL_TimerA_setCaptureCompareValue(htim, duty, channel);
}

void N20_Motor::output_intensity()//1ms进行一次输出
{
    INRANGE(this->intensity, PWM_DUTY_MAX);//防止占空比溢出
    switch(this->state)//motor的三种状态对应不同的输出
    {

    case MOTOR_STOP:
    {
        this->intensity = 0;
        pwm_set_duty(pwm_channel1, PWM_DUTY_MAX);
        pwm_set_duty(pwm_channel2, PWM_DUTY_MAX);

    }break;

    case MOTOR_RUN:
    {
        if(this->intensity < 0)
        {
            pwm_set_duty(pwm_channel1, PWM_DUTY_MAX - ABS(this->intensity));
            pwm_set_duty(pwm_channel2, PWM_DUTY_MAX);
        }
        else
        {
            pwm_set_duty(pwm_channel1, PWM_DUTY_MAX);
            pwm_set_duty(pwm_channel2, PWM_DUTY_MAX - ABS(this->intensity));
        }

    }break;

    case MOTOR_RELEASE:
    {
        this->intensity = 0;
        pwm_set_duty(pwm_channel1, 0);
        pwm_set_duty(pwm_channel2, 0);
    }
        break;
    }

}

N20_Motor::N20_Motor(GPTIMER_Regs *htim, DL_TIMER_CC_INDEX pwm_channel1, DL_TIMER_CC_INDEX pwm_channel2, Encoder *encoder,
                     float reduction_rate, float radius) {
    this->htim = htim;
    this->pwm_channel1 = pwm_channel1;
    this->pwm_channel2 = pwm_channel2;
    this->encoder = encoder;
    this->reduction_rate = reduction_rate;
    this->radius = radius;

}

void N20_Motor::init() {
    DL_Timer_startCounter(htim);
}
