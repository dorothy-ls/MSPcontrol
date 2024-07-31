#ifndef CONTROL_CCD_H
#define CONTROL_CCD_H

#include "hal.h"

class CCD{
public:
    int integrate_time = 10;
    uint16_t data[128];//�洢����CCD���ݣ�16λ
    int sample_t = 0;
    bool sample_complete = false;

    uint8_t bin_ccd[128];
    uint16_t dir;   //����λ��
    uint16_t last_dir;
    uint16_t threshold;//�ڰ׷ֽ�Ķ�̬��ֵ

    void init();
    void Handler(); //����������ѭ����
    void SI_send(); //���ڶ�ʱ���ж���
//    void GetThreshold();
//    void Binarization();
//    void Filter();
//    uint16_t GetDirection();
//    void Line_tracing();

private:
    int state = 0;

};
#endif
