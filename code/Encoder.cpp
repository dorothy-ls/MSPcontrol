#include "Encoder.h"

#define CNT_OVERFLOW 65536

//systick中断调用
void Encoder::Handler() {
    pulse += *CNT - prev_cnt + carry_flag * CNT_OVERFLOW;
    carry_flag = 0;
    prev_cnt = *CNT;
}

Encoder::Encoder(uint16_t* CNT_ADD) {
    CNT = CNT_ADD;
}

//void Encoder::init() {
//    NVIC_EnableIRQ(TIM_ENCODE_INST_INT_IRQN);
//    DL_Timer_startCounter(TIM_ENCODE_INST);
//
//    HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
//    HAL_TIM_Base_Start_IT(htim);
//}

//虚拟溢出中断回调
void Encoder::overflow_update() {
//    if(!init_flag){
//        init_flag = true;
//        return;
//    }
    if(*CNT < CNT_OVERFLOW / 2) carry_flag++;
    else carry_flag--;
}
