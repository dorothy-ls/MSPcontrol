#ifndef CONTROL_CCD_H
#define CONTROL_CCD_H

#include "ti_msp_dl_config.h"

class CCD{
public:
    int integrate_time = 10;
    uint16_t data[128];//存储线性CCD数据，16位
    int sample_t = 0;
    bool sample_complete = false;

    uint8_t bin_ccd[128];
    uint16_t dir;   //黑线位置
    uint16_t last_dir;
    uint16_t threshold;//黑白分界的动态阈值

    void init();
    void Handler(); //放在主任务循环里
    void SI_send(); //放在定时器中断里
//    void GetThreshold();
//    void Binarization();
//    void Filter();
//    uint16_t GetDirection();
//    void Line_tracing();

private:
    int state = 0;

};
#endif
