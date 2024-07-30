#ifndef CONTROL_MOTOR_H
#define CONTROL_MOTOR_H

#include "ti_msp_dl_config.h"

typedef enum{
    MOTOR_STOP = 0,
    MOTOR_RUN,
    MOTOR_RELEASE
} motor_state;//枚举类型

class Motor{
public:
    motor_state state = MOTOR_STOP;
    int16_t intensity = 0;//电流强度(有正负方向)
    float ang = 0;  // (degree)
    float v = 0;    // m/s

};

#endif
