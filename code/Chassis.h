#ifndef CONTROL_CHASSIS_H
#define CONTROL_CHASSIS_H

#include "module.h"
#include "algorithm.h"

typedef enum{
    CHASSIS_STOP = 0,
    CHASSIS_RUN = 1,
    CHASSIS_RELEASE
} chassis_state;

class Chassis {
public:
    chassis_state state;

    N20_Motor* motorL;
    N20_Motor* motorR;

    IMU* imu;
    CCD* ccd;

    float wheel_seperation;

    Chassis(N20_Motor* left_motor, N20_Motor* right_motor, IMU* imu, CCD* ccd,
            float wheel_seperation);

    //�˶���Ϣ
    float v = 0;
    float w = 0;
    float ang = 0;
    float ang1 = 0, ang2 = 0;

    float x = 0, y = 0;

    float v_set = 0, w_set = 0; //0-10000

    //��Ұ����
//    float D = 8.8 / 100;
//    float dl = 8.0 / 100 / 88;
    float D = 9.8 / 100;
    float dl = 8.0 / 100 / 95;

    //���ʶ����Ϣ
    bool inrange = false;
    float mid_point = 0;
    float x_line = 0, y_line = 0;   //�������


    void Handler();
    void process();

private:
    float data_norm[128];
    uint8_t bin_ccd[128];
    float threshold;

};


#endif //CONTROL_CHASSIS_H
