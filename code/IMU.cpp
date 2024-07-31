#include "IMU.h"
#include "imu660.h"
#include "imu963ra.h"

#define IMU_CALIBRATE_N 1000
void IMU::get_data(){
#ifdef USE_IMU660RA
    imu660ra_get_acc();                                                         // ��ȡ IMU660RA �ļ��ٶȲ�����ֵ
    imu660ra_get_gyro();

    this->ax = this->ax * k_imu + (1 - k_imu) * (imu660ra_acc_transition(imu660ra_acc_x) - ax_offset);
    this->ay = this->ay * k_imu + (1 - k_imu) * (imu660ra_acc_transition(imu660ra_acc_y) - ay_offset);
    this->az = this->az * k_imu + (1 - k_imu) * (imu660ra_acc_transition(imu660ra_acc_z) - az_offset);
    this->wx = this->wx * k_imu + (1 - k_imu) * (imu660ra_gyro_transition(imu660ra_gyro_x) - wx_offset);
    this->wy = this->wy * k_imu + (1 - k_imu) * (imu660ra_gyro_transition(imu660ra_gyro_y) - wy_offset);
    this->wz = this->wz * k_imu + (1 - k_imu) * (imu660ra_gyro_transition(imu660ra_gyro_z) - wz_offset);
#endif

#ifdef USE_IMU963RA
    imu963ra_get_acc();                                                         // ��ȡ IMU660RA �ļ��ٶȲ�����ֵ
    imu963ra_get_gyro();
    imu963ra_get_mag();

    this->ax = this->ax * k_imu + (1 - k_imu) * (imu963ra_acc_transition(imu963ra_acc_x) - ax_offset);
    this->ay = this->ay * k_imu + (1 - k_imu) * (imu963ra_acc_transition(imu963ra_acc_y) - ay_offset);
    this->az = this->az * k_imu + (1 - k_imu) * (imu963ra_acc_transition(imu963ra_acc_z) - az_offset);
    this->wx = this->wx * k_imu + (1 - k_imu) * (imu963ra_gyro_transition(imu963ra_gyro_x) - wx_offset);
    this->wy = this->wy * k_imu + (1 - k_imu) * (imu963ra_gyro_transition(imu963ra_gyro_y) - wy_offset);
    this->wz = this->wz * k_imu + (1 - k_imu) * (imu963ra_gyro_transition(imu963ra_gyro_z) - wz_offset);

    this->gx = imu963ra_gyro_transition(imu963ra_mag_x);
    this->gy = imu963ra_gyro_transition(imu963ra_mag_y);
    this->gz = imu963ra_gyro_transition(imu963ra_mag_z);

#endif
}

void IMU::init() {
#ifdef USE_IMU660RA
    if(imu660ra_init()) this->state = IMU_ERR;
    else this->state = IMU_CALIBRATE;

    delay_ms(10);
    if(this->state == IMU_CALIBRATE){
        //calibrate
        float ax_mean = 0, ay_mean = 0, az_mean = 0, wx_mean = 0, wy_mean = 0, wz_mean = 0;
        for(int i = 0; i < IMU_CALIBRATE_N; i++){
           get_data();
           ax_mean += ax;
           ay_mean += ay;
           az_mean += az;
           wx_mean += wx;
           wy_mean += wy;
           wz_mean += wz;
           delay_ms(1);
        }
        //��бУ��

        ax_offset = ax_mean / IMU_CALIBRATE_N;
        ay_offset = ay_mean / IMU_CALIBRATE_N;
        az_offset = az_mean / IMU_CALIBRATE_N;
        wx_offset = wx_mean / IMU_CALIBRATE_N;
        wy_offset = wy_mean / IMU_CALIBRATE_N;
        wz_offset = wz_mean / IMU_CALIBRATE_N;
        state = IMU_RUN;
    }
#endif

#ifdef USE_IMU963RA
    if(imu963ra_init()) this->state = IMU_ERR;
    else this->state = IMU_CALIBRATE;

    delay_ms(10);
    if(this->state == IMU_CALIBRATE){
        //calibrate
        float ax_mean = 0, ay_mean = 0, az_mean = 0, wx_mean = 0, wy_mean = 0, wz_mean = 0;
        for(int i = 0; i < IMU_CALIBRATE_N; i++){
           get_data();
           ax_mean += ax;
           ay_mean += ay;
           az_mean += az;
           wx_mean += wx;
           wy_mean += wy;
           wz_mean += wz;
           delay_ms(1);
        }
        //��бУ��

        ax_offset = ax_mean / IMU_CALIBRATE_N;
        ay_offset = ay_mean / IMU_CALIBRATE_N;
        az_offset = az_mean / IMU_CALIBRATE_N;
        wx_offset = wx_mean / IMU_CALIBRATE_N;
        wy_offset = wy_mean / IMU_CALIBRATE_N;
        wz_offset = wz_mean / IMU_CALIBRATE_N;
        state = IMU_RUN;
    }
#endif
}
void IMU::Handler()
{
    if(this->state == IMU_RUN)
    {
        get_data();

//        float temp_cos, temp_sin;
//        arm_sin_cos_f32(correct_ang, &temp_sin, &temp_cos);
//        ax_correct = ax * temp_cos - ay * temp_sin;
//        ay_correct = ay * temp_cos + ax * temp_sin;
    }
}
