#ifndef CONTROL_ENCODER_H
#define CONTROL_ENCODER_H

#include "ti_msp_dl_config.h"

class Encoder{
public:
    int32_t pulse = 0;//脉冲个数，有符号
    Encoder(long* CNT_ADD);//绑定QEI库定义的虚拟CNT

    void init();
    void Handler(); //更新角度，放在主程序任务轮询中断里
    void overflow_update(); //放在定时器update中断里
private:
    long* CNT;//编码器对应GPIO通道

    int carry_flag = 0;
    long prev_cnt = 0;

    bool init_flag = false;//初始化是否完成，初始化处理和一般处理不同

};
#endif
