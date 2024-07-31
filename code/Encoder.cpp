/**
  ******************************************************************************
  * @FileName			    Encoder.h
  * @Description
  * @author                 Yu Xinyi
  * @note
  ******************************************************************************
  *
  * Copyright (c) 2023 Team JiaoLong-ShanghaiJiaoTong University
  * All rights reserved.
  *
  ******************************************************************************
**/

#include "Encoder.h"

#define CNT_OVERFLOW 4294967296
#define CNT_TH1 1073741824
#define CNT_TH2 3221225472

void Encoder::Handler() {
    if(*CNT < CNT_TH1 && prev_cnt > CNT_TH2){ //向上溢出
        carry_flag++;
    }else if(*CNT > CNT_TH2 && prev_cnt < CNT_TH1){ //向下溢出
        carry_flag--;
    }
    pulse += *CNT + (carry_flag * CNT_OVERFLOW - prev_cnt);
    carry_flag = 0;
    prev_cnt = *CNT;

}

Encoder::Encoder(uint32_t* CNT) {
    this->CNT = CNT;
}

