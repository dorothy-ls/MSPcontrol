#ifndef _zf_device_imu963ra_h
#define _zf_device_imu963ra_h


#ifdef __cplusplus
extern "C" {
#endif
	
#include "hal.h"

#define IMU963RA_USE_SOFT_IIC                       (0)                         // Ĭ��ʹ��Ӳ�� SPI ��ʽ����

//====================================================Ӳ�� SPI ����====================================================
#define IMU963RA_SPI_SPEED                          (8000000)          // Ӳ�� SPI ����
#define IMU963RA_SPI                                SPI_IMU_INST             // Ӳ�� SPI ��
//====================================================Ӳ�� SPI ����====================================================

//#define IMU963RA_CS(x)                               ((x) ? (HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_SET)) : (HAL_GPIO_WritePin(SPI2_CS_GPIO_Port, SPI2_CS_Pin, GPIO_PIN_RESET)))
#define IMU963RA_CS(x)              ((x) ? (DL_GPIO_setPins(GPIO_SPI_PORT, GPIO_SPI_PIN_SPI_CS_PIN)) : (DL_GPIO_clearPins(GPIO_SPI_PORT, GPIO_SPI_PIN_SPI_CS_PIN)))
typedef enum
{
    IMU963RA_ACC_SAMPLE_SGN_2G ,                                                // ���ٶȼ����� ��2G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    IMU963RA_ACC_SAMPLE_SGN_4G ,                                                // ���ٶȼ����� ��4G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    IMU963RA_ACC_SAMPLE_SGN_8G ,                                                // ���ٶȼ����� ��8G  (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
    IMU963RA_ACC_SAMPLE_SGN_16G,                                                // ���ٶȼ����� ��16G (ACC = Accelerometer ���ٶȼ�) (SGN = signum �������� ��ʾ������Χ) (G = g �������ٶ� g��9.80 m/s^2)
}imu963ra_acc_sample_config;

typedef enum
{
    IMU963RA_GYRO_SAMPLE_SGN_125DPS ,                                           // ���������� ��125DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU963RA_GYRO_SAMPLE_SGN_250DPS ,                                           // ���������� ��250DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU963RA_GYRO_SAMPLE_SGN_500DPS ,                                           // ���������� ��500DPS  (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU963RA_GYRO_SAMPLE_SGN_1000DPS,                                           // ���������� ��1000DPS (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU963RA_GYRO_SAMPLE_SGN_2000DPS,                                           // ���������� ��2000DPS (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
    IMU963RA_GYRO_SAMPLE_SGN_4000DPS,                                           // ���������� ��4000DPS (GYRO = Gyroscope ������) (SGN = signum �������� ��ʾ������Χ) (DPS = Degree Per Second ���ٶȵ�λ ��/S)
}imu963ra_gyro_sample_config;

typedef enum
{
    IMU963RA_MAG_SAMPLE_2G,                                                     // ���������� 2G (MAG = Magnetometer ������) (G = Gs ��˹)
    IMU963RA_MAG_SAMPLE_8G,                                                     // ���������� 8G (MAG = Magnetometer ������) (G = Gs ��˹)
}imu963ra_mag_sample_config;

#define IMU963RA_ACC_SAMPLE_DEFAULT     ( IMU963RA_ACC_SAMPLE_SGN_8G )          // ��������Ĭ�ϵ� ���ٶȼ� ��ʼ������
#define IMU963RA_GYRO_SAMPLE_DEFAULT    ( IMU963RA_GYRO_SAMPLE_SGN_2000DPS )    // ��������Ĭ�ϵ� ������   ��ʼ������
#define IMU963RA_MAG_SAMPLE_DEFAULT     ( IMU963RA_MAG_SAMPLE_8G )              // ��������Ĭ�ϵ� ������   ��ʼ������

#define IMU963RA_TIMEOUT_COUNT                      ( 0x00FF )                  // IMU963RA ��ʱ����

//================================================���� IMU963RA �ڲ���ַ================================================
#define IMU963RA_DEV_ADDR                           ( 0x6B )                    // SA0�ӵأ�0x6A SA0������0x6B ģ��Ĭ������
#define IMU963RA_SPI_W                              ( 0x00 )
#define IMU963RA_SPI_R                              ( 0x80 )

#define IMU963RA_FUNC_CFG_ACCESS                    ( 0x01 )
#define IMU963RA_PIN_CTRL                           ( 0x02 )
#define IMU963RA_S4S_TPH_L                          ( 0x04 )
#define IMU963RA_S4S_TPH_H                          ( 0x05 )
#define IMU963RA_S4S_RR                             ( 0x06 )
#define IMU963RA_FIFO_CTRL1                         ( 0x07 )
#define IMU963RA_FIFO_CTRL2                         ( 0x08 )
#define IMU963RA_FIFO_CTRL3                         ( 0x09 )
#define IMU963RA_FIFO_CTRL4                         ( 0x0A )
#define IMU963RA_COUNTER_BDR_REG1                   ( 0x0B )
#define IMU963RA_COUNTER_BDR_REG2                   ( 0x0C )
#define IMU963RA_INT1_CTRL                          ( 0x0D )
#define IMU963RA_INT2_CTRL                          ( 0x0E )
#define IMU963RA_WHO_AM_I                           ( 0x0F )
#define IMU963RA_CTRL1_XL                           ( 0x10 )
#define IMU963RA_CTRL2_G                            ( 0x11 )
#define IMU963RA_CTRL3_C                            ( 0x12 )
#define IMU963RA_CTRL4_C                            ( 0x13 )
#define IMU963RA_CTRL5_C                            ( 0x14 )
#define IMU963RA_CTRL6_C                            ( 0x15 )
#define IMU963RA_CTRL7_G                            ( 0x16 )
#define IMU963RA_CTRL8_XL                           ( 0x17 )
#define IMU963RA_CTRL9_XL                           ( 0x18 )
#define IMU963RA_CTRL10_C                           ( 0x19 )
#define IMU963RA_ALL_INT_SRC                        ( 0x1A )
#define IMU963RA_WAKE_UP_SRC                        ( 0x1B )
#define IMU963RA_TAP_SRC                            ( 0x1C )
#define IMU963RA_D6D_SRC                            ( 0x1D )
#define IMU963RA_STATUS_REG                         ( 0x1E )
#define IMU963RA_OUT_TEMP_L                         ( 0x20 )
#define IMU963RA_OUT_TEMP_H                         ( 0x21 )
#define IMU963RA_OUTX_L_G                           ( 0x22 )
#define IMU963RA_OUTX_H_G                           ( 0x23 )
#define IMU963RA_OUTY_L_G                           ( 0x24 )
#define IMU963RA_OUTY_H_G                           ( 0x25 )
#define IMU963RA_OUTZ_L_G                           ( 0x26 )
#define IMU963RA_OUTZ_H_G                           ( 0x27 )
#define IMU963RA_OUTX_L_A                           ( 0x28 )
#define IMU963RA_OUTX_H_A                           ( 0x29 )
#define IMU963RA_OUTY_L_A                           ( 0x2A )
#define IMU963RA_OUTY_H_A                           ( 0x2B )
#define IMU963RA_OUTZ_L_A                           ( 0x2C )
#define IMU963RA_OUTZ_H_A                           ( 0x2D )
#define IMU963RA_EMB_FUNC_STATUS_MAINPAGE           ( 0x35 )
#define IMU963RA_FSM_STATUS_A_MAINPAGE              ( 0x36 )
#define IMU963RA_FSM_STATUS_B_MAINPAGE              ( 0x37 )
#define IMU963RA_STATUS_MASTER_MAINPAGE             ( 0x39 )
#define IMU963RA_FIFO_STATUS1                       ( 0x3A )
#define IMU963RA_FIFO_STATUS2                       ( 0x3B )
#define IMU963RA_TIMESTAMP0                         ( 0x40 )
#define IMU963RA_TIMESTAMP1                         ( 0x41 )
#define IMU963RA_TIMESTAMP2                         ( 0x42 )
#define IMU963RA_TIMESTAMP3                         ( 0x43 )
#define IMU963RA_TAP_CFG0                           ( 0x56 )
#define IMU963RA_TAP_CFG1                           ( 0x57 )
#define IMU963RA_TAP_CFG2                           ( 0x58 )
#define IMU963RA_TAP_THS_6D                         ( 0x59 )
#define IMU963RA_INT_DUR2                           ( 0x5A )
#define IMU963RA_WAKE_UP_THS                        ( 0x5B )
#define IMU963RA_WAKE_UP_DUR                        ( 0x5C )
#define IMU963RA_FREE_FALL                          ( 0x5D )
#define IMU963RA_MD1_CFG                            ( 0x5E )
#define IMU963RA_MD2_CFG                            ( 0x5F )
#define IMU963RA_S4S_ST_CMD_CODE                    ( 0x60 )
#define IMU963RA_S4S_DT_REG                         ( 0x61 )
#define IMU963RA_I3C_BUS_AVB                        ( 0x62 )
#define IMU963RA_INTERNAL_FREQ_FINE                 ( 0x63 )
#define IMU963RA_INT_OIS                            ( 0x6F )
#define IMU963RA_CTRL1_OIS                          ( 0x70 )
#define IMU963RA_CTRL2_OIS                          ( 0x71 )
#define IMU963RA_CTRL3_OIS                          ( 0x72 )
#define IMU963RA_X_OFS_USR                          ( 0x73 )
#define IMU963RA_Y_OFS_USR                          ( 0x74 )
#define IMU963RA_Z_OFS_USR                          ( 0x75 )
#define IMU963RA_FIFO_DATA_OUT_TAG                  ( 0x78 )
#define IMU963RA_FIFO_DATA_OUT_X_L                  ( 0x79 )
#define IMU963RA_FIFO_DATA_OUT_X_H                  ( 0x7A )
#define IMU963RA_FIFO_DATA_OUT_Y_L                  ( 0x7B )
#define IMU963RA_FIFO_DATA_OUT_Y_H                  ( 0x7C )
#define IMU963RA_FIFO_DATA_OUT_Z_L                  ( 0x7D )
#define IMU963RA_FIFO_DATA_OUT_Z_H                  ( 0x7E )

// ������������ؼĴ��� ��Ҫ��FUNC_CFG_ACCESS��SHUB_REG_ACCESSλ����Ϊ1������ȷ����
#define IMU963RA_SENSOR_HUB_1                       ( 0x02 ) 
#define IMU963RA_SENSOR_HUB_2                       ( 0x03 ) 
#define IMU963RA_SENSOR_HUB_3                       ( 0x04 ) 
#define IMU963RA_SENSOR_HUB_4                       ( 0x05 ) 
#define IMU963RA_SENSOR_HUB_5                       ( 0x06 ) 
#define IMU963RA_SENSOR_HUB_6                       ( 0x07 ) 
#define IMU963RA_SENSOR_HUB_7                       ( 0x08 ) 
#define IMU963RA_SENSOR_HUB_8                       ( 0x09 ) 
#define IMU963RA_SENSOR_HUB_9                       ( 0x0A ) 
#define IMU963RA_SENSOR_HUB_10                      ( 0x0B ) 
#define IMU963RA_SENSOR_HUB_11                      ( 0x0C ) 
#define IMU963RA_SENSOR_HUB_12                      ( 0x0D ) 
#define IMU963RA_SENSOR_HUB_13                      ( 0x0E ) 
#define IMU963RA_SENSOR_HUB_14                      ( 0x0F ) 
#define IMU963RA_SENSOR_HUB_15                      ( 0x10 ) 
#define IMU963RA_SENSOR_HUB_16                      ( 0x11 ) 
#define IMU963RA_SENSOR_HUB_17                      ( 0x12 ) 
#define IMU963RA_SENSOR_HUB_18                      ( 0x13 ) 
#define IMU963RA_MASTER_CONFIG                      ( 0x14 ) 
#define IMU963RA_SLV0_ADD                           ( 0x15 ) 
#define IMU963RA_SLV0_SUBADD                        ( 0x16 ) 
#define IMU963RA_SLV0_CONFIG                        ( 0x17 ) 
#define IMU963RA_SLV1_ADD                           ( 0x18 ) 
#define IMU963RA_SLV1_SUBADD                        ( 0x19 ) 
#define IMU963RA_SLV1_CONFIG                        ( 0x1A ) 
#define IMU963RA_SLV2_ADD                           ( 0x1B ) 
#define IMU963RA_SLV2_SUBADD                        ( 0x1C ) 
#define IMU963RA_SLV2_CONFIG                        ( 0x1D ) 
#define IMU963RA_SLV3_ADD                           ( 0x1E ) 
#define IMU963RA_SLV3_SUBADD                        ( 0x1F ) 
#define IMU963RA_SLV3_CONFIG                        ( 0x20 ) 
#define IMU963RA_DATAWRITE_SLV0                     ( 0x21 ) 
#define IMU963RA_STATUS_MASTER                      ( 0x22 )

#define IMU963RA_MAG_ADDR                           ( 0x0D )                    // 7λIIC��ַ
#define IMU963RA_MAG_OUTX_L                         ( 0x00 )
#define IMU963RA_MAG_CONTROL1                       ( 0x09 )
#define IMU963RA_MAG_CONTROL2                       ( 0x0A )
#define IMU963RA_MAG_FBR                            ( 0x0B )
#define IMU963RA_MAG_CHIP_ID                        ( 0x0D )
//================================================���� IMU963RA �ڲ���ַ================================================

extern int16_t imu963ra_acc_x,  imu963ra_acc_y,  imu963ra_acc_z;
extern int16_t imu963ra_gyro_x, imu963ra_gyro_y, imu963ra_gyro_z;
extern int16_t imu963ra_mag_x,  imu963ra_mag_y,  imu963ra_mag_z;
extern float imu963ra_transition_factor[3];
extern int imu963ra_state;

void    imu963ra_get_acc            (void);
void    imu963ra_get_gyro           (void);
void    imu963ra_get_mag            (void);

//-------------------------------------------------------------------------------------------------------------------
// �������     �� IMU963RA ���ٶȼ�����ת��Ϊʵ����������
// ����˵��     acc_value       ������ļ��ٶȼ�����
// ���ز���     void
// ʹ��ʾ��     float data = imu963ra_acc_transition(imu963ra_acc_x);           // ��λΪ g(m/s^2)
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define imu963ra_acc_transition(acc_value)      ((float)acc_value / imu963ra_transition_factor[0])

//-------------------------------------------------------------------------------------------------------------------
// �������     �� IMU963RA ����������ת��Ϊʵ����������
// ����˵��     gyro_value      �����������������
// ���ز���     void
// ʹ��ʾ��     float data = imu963ra_gyro_transition(imu963ra_gyro_x);         // ��λΪ ��/s
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define imu963ra_gyro_transition(gyro_value)    ((float)gyro_value / imu963ra_transition_factor[1])

//-------------------------------------------------------------------------------------------------------------------
// �������     �� IMU963RA ����������ת��Ϊʵ����������
// ����˵��     mag_value       ������Ĵ���������
// ���ز���     void
// ʹ��ʾ��     float data = imu963ra_mag_transition(imu963ra_mag_x);           // ��λΪ G
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
#define imu963ra_mag_transition(mag_value)    ((float)mag_value / imu963ra_transition_factor[2])

uint8_t   imu963ra_init               (void);


#ifdef __cplusplus
}
#endif
	
#endif