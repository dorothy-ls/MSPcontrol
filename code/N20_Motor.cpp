#include "N20_Motor.h"

#define ENCODER_FREQ 1000
void N20_Motor::Handler() //systick IRQ
{
    measure_parameter();//1ms��ȡһ�η�������
    output_intensity();//1ms����һ�����
}

void N20_Motor::measure_parameter()//��ȡ��ǰ�������ٶȺͽǶ�
{
    float inc = -(float)encoder->pulse / this->reduction_rate * 360;//��������ת��Ϊ�Ƕȣ�degree��
    inc_pulse = encoder->pulse;
    encoder->pulse = 0;//��ȡһ��encoder��pulse��������㣬��С�ۼ����
    float v_temp = inc / 180 * M_PI *  ENCODER_FREQ * radius;//���ٶ�ת��Ϊ���ٶ�
    if(v_temp < 0.35 && v_temp > -0.35){
        this->v = v_temp;
        //this->ang += inc;
    }
    /*if(this->ang >= 360){
        this->ang -= (int)(this->ang / 360) * 360;
    }else if(this->ang < 0){
        this->ang -= (int)(this->ang / 360) * 360 - 360;
    }//���ֽǶ���0-360*/
}



void N20_Motor::pwm_set_duty(DL_TIMER_CC_INDEX channel, uint16_t duty)
{ //0-5000 TODO cube����
    DL_TimerA_setCaptureCompareValue(htim, duty, channel);
}

void N20_Motor::output_intensity()//1ms����һ�����
{
    INRANGE(this->intensity, PWM_DUTY_MAX);//��ֹռ�ձ����
    switch(this->state)//motor������״̬��Ӧ��ͬ�����
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
            pwm_set_duty(pwm_channel1, PWM_DUTY_MAX - (int)MAP(ABS(this->intensity), 0, PWM_DUTY_MAX, this->deadzone, PWM_DUTY_MAX));
            pwm_set_duty(pwm_channel2, PWM_DUTY_MAX);
        }
        else
        {
            pwm_set_duty(pwm_channel1, PWM_DUTY_MAX);
            pwm_set_duty(pwm_channel2, PWM_DUTY_MAX - (int)MAP(ABS(this->intensity), 0, PWM_DUTY_MAX, this->deadzone, PWM_DUTY_MAX));
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
                     float reduction_rate, float radius, float deadzone) {
    this->htim = htim;
    this->pwm_channel1 = pwm_channel1;
    this->pwm_channel2 = pwm_channel2;
    this->encoder = encoder;
    this->reduction_rate = reduction_rate;
    this->radius = radius;
    this->deadzone = deadzone;

}

void N20_Motor::init() {
    DL_Timer_startCounter(htim);
}
