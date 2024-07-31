#ifndef CONTROL_IMU660_H
#define CONTROL_IMU660_H

#ifdef __cplusplus
extern "C" {
#endif

#include "hal.h"


// IMU660RA_USE_SOFT_IIC����Ϊ0��ʾʹ��Ӳ��SPI���� ����Ϊ1��ʾʹ�����IIC����
// ������IMU660RA_USE_SOFT_IIC�������Ҫ�ȱ��벢���س��򣬵�Ƭ����ģ����Ҫ�ϵ�������������ͨѶ
#define IMU660RA_USE_SOFT_IIC         (0)                                       // Ĭ��ʹ��Ӳ�� SPI ��ʽ����


#if IMU660RA_USE_SOFT_IIC                                                       // ������ ��ɫ�����Ĳ�����ȷ�� ��ɫ�ҵľ���û���õ�
//====================================================��� IIC ����====================================================
#define IMU660RA_SOFT_IIC_DELAY     (100)                                       // ��� IIC ��ʱ����ʱ���� ��ֵԽС IIC ͨ������Խ��
#define IMU660RA_SCL_PIN            (C23)                                       // ��� IIC SCL ���� ���� IMU660RA �� SCL ����
#define IMU660RA_SDA_PIN            (C22)                                       // ��� IIC SDA ���� ���� IMU660RA �� SDA ����
//====================================================��� IIC ����====================================================
#else

//====================================================Ӳ�� SPI ����====================================================
#define IMU660RA_SPI_SPEED          (8000000)                          // Ӳ�� SPI ����
#define IMU660RA_SPI    SPI_IMU_INST
//====================================================Ӳ�� SPI ����====================================================
#endif
//#define IMU660RA_CS(x)              ((x) ? (HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET)))
#define IMU660RA_CS(x)              ((x) ? (DL_GPIO_setPins(GPIO_SPI_PORT, GPIO_SPI_PIN_SPI_CS_PIN)) : (DL_GPIO_clearPins(GPIO_SPI_PORT, GPIO_SPI_PIN_SPI_CS_PIN)))


typedef enum {
    IMU660RA_ACC_SAMPLE_SGN_2G,                                                // ���ٶȼ����� ��2G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    IMU660RA_ACC_SAMPLE_SGN_4G,                                                // ���ٶȼ����� ��4G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    IMU660RA_ACC_SAMPLE_SGN_8G,                                                // ���ٶȼ����� ��8G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    IMU660RA_ACC_SAMPLE_SGN_16G,                                                // ���ٶȼ����� ��16G (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
} imu660ra_acc_sample_config;

typedef enum {
    IMU660RA_GYRO_SAMPLE_SGN_125DPS,                                           // ���������� ��125DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU660RA_GYRO_SAMPLE_SGN_250DPS,                                           // ���������� ��250DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU660RA_GYRO_SAMPLE_SGN_500DPS,                                           // ���������� ��500DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU660RA_GYRO_SAMPLE_SGN_1000DPS,                                           // ���������� ��1000DPS (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU660RA_GYRO_SAMPLE_SGN_2000DPS,                                           // ���������� ��2000DPS (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
} imu660ra_gyro_sample_config;

#define IMU660RA_ACC_SAMPLE_DEFAULT     ( IMU660RA_ACC_SAMPLE_SGN_2G )          // ��������Ĭ�ϵ� ���ٶȼ� ��ʼ������
#define IMU660RA_GYRO_SAMPLE_DEFAULT    ( IMU660RA_GYRO_SAMPLE_SGN_2000DPS )    // ��������Ĭ�ϵ� ������   ��ʼ������

#define IMU660RA_TIMEOUT_COUNT      ( 0x00FF )                                  // IMU660RA ��ʱ����

//================================================���� IMU660RA �ڲ���ַ================================================
#define IMU660RA_DEV_ADDR           ( 0x69 )                                    // SA0�ӵأ�0x68 SA0������0x69 ģ��Ĭ������
#define IMU660RA_SPI_W              ( 0x00 )
#define IMU660RA_SPI_R              ( 0x80 )

#define IMU660RA_CHIP_ID            ( 0x00 )
#define IMU660RA_PWR_CONF           ( 0x7C )
#define IMU660RA_PWR_CTRL           ( 0x7D )
#define IMU660RA_INIT_CTRL          ( 0x59 )
#define IMU660RA_INIT_DATA          ( 0x5E )
#define IMU660RA_INT_STA            ( 0x21 )
#define IMU660RA_ACC_ADDRESS        ( 0x0C )
#define IMU660RA_GYRO_ADDRESS       ( 0x12 )
#define IMU660RA_ACC_CONF           ( 0x40 )
#define IMU660RA_ACC_RANGE          ( 0x41 )
#define IMU660RA_GYR_CONF           ( 0x42 )
#define IMU660RA_GYR_RANGE          ( 0x43 )
//================================================���� IMU660RA �ڲ���ַ================================================

extern int16_t imu660ra_gyro_x, imu660ra_gyro_y, imu660ra_gyro_z;                 // ��������������      gyro (������)
extern int16_t imu660ra_acc_x, imu660ra_acc_y, imu660ra_acc_z;                    // ������ٶȼ�����     acc (accelerometer ���ٶȼ�)
extern float imu660ra_transition_factor[2];
extern int imu660ra_state;

void imu660ra_get_acc(void);                                     // ��ȡ IMU660RA ���ٶȼ�����
void imu660ra_get_gyro(void);                                     // ��ȡ IMU660RA ����������

//-------------------------------------------------------------------------------------------------------------------
// �������     �� IMU660RA ���ٶȼ�����ת��Ϊʵ����������
// ����˵��     acc_value       ������ļ��ٶȼ�����
// ���ز���     void
// ʹ��ʾ��     float data = imu660ra_acc_transition(imu660ra_acc_x);           // ��λΪ g(m/s^2)
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define imu660ra_acc_transition(acc_value)      ((float)acc_value / imu660ra_transition_factor[0])

//-------------------------------------------------------------------------------------------------------------------
// �������     �� IMU660RA ����������ת��Ϊʵ����������
// ����˵��     gyro_value      �����������������
// ���ز���     void
// ʹ��ʾ��     float data = imu660ra_gyro_transition(imu660ra_gyro_x);         // ��λΪ ��/s
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define imu660ra_gyro_transition(gyro_value)    ((float)gyro_value / imu660ra_transition_factor[1])

uint8_t imu660ra_init(void);                                     // ��ʼ�� IMU660RA



#ifdef __cplusplus
}
#endif


#endif //CONTROL_IMU660_H
