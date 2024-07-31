#ifndef CONTROL_ENCODER_H
#define CONTROL_ENCODER_H

#include "ti_msp_dl_config.h"

class Encoder{
public:
    int32_t pulse = 0;//����������з���
    Encoder(long* CNT_ADD);//��QEI�ⶨ�������CNT

    void init();
    void Handler(); //���½Ƕȣ�����������������ѯ�ж���
    void overflow_update(); //���ڶ�ʱ��update�ж���
private:
    long* CNT;//��������ӦGPIOͨ��

    int carry_flag = 0;
    long prev_cnt = 0;

    bool init_flag = false;//��ʼ���Ƿ���ɣ���ʼ�������һ�㴦��ͬ

};
#endif
