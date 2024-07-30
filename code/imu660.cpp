#include "imu660.h"
#include "imu660_config.h"
#include "it.h"


int16_t imu660ra_gyro_x = 0, imu660ra_gyro_y = 0, imu660ra_gyro_z = 0;            // ��������������   gyro (������)
int16_t imu660ra_acc_x = 0, imu660ra_acc_y = 0, imu660ra_acc_z = 0;               // ������ٶȼ����� acc  (accelerometer ���ٶȼ�)
float imu660ra_transition_factor[2] = {4096, 16.4};


//-------------------------------------------------------------------------------------------------------------------
// �������     IMU660RA д�Ĵ���
// ����˵��     reg             �Ĵ�����ַ
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     imu660ra_write_register(IMU660RA_PWR_CONF, 0x00);                   // �رո߼�ʡ��ģʽ
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void imu660ra_write_register (uint8_t reg, uint8_t data)
{
    IMU660RA_CS(0);
    spi_write_8bit_register(IMU660RA_SPI, reg | IMU660RA_SPI_W, data);
    IMU660RA_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IMU660RA д����
// ����˵��     reg             �Ĵ�����ַ
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     imu660ra_write_registers(IMU660RA_INIT_DATA, imu660ra_config_file, sizeof(imu660ra_config_file));
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void imu660ra_write_registers (uint8_t reg, const uint8_t *data, uint32_t len)
{
    IMU660RA_CS(0);
    spi_write_8bit_registers(IMU660RA_SPI, reg | IMU660RA_SPI_W, (uint8_t*)data, len);
    IMU660RA_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IMU660RA ���Ĵ���
// ����˵��     reg             �Ĵ�����ַ
// ���ز���     uint8           ����
// ʹ��ʾ��     imu660ra_read_register(IMU660RA_CHIP_ID);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t imu660ra_read_register (uint8_t reg)
{
    uint8_t data[2];
    IMU660RA_CS(0);
    spi_read_8bit_registers(IMU660RA_SPI, reg | IMU660RA_SPI_R, data, 2);
    IMU660RA_CS(1);
    return data[1];
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IMU660RA ������
// ����˵��     reg             �Ĵ�����ַ
// ����˵��     data            ���ݻ�����
// ����˵��     len             ���ݳ���
// ���ز���     void
// ʹ��ʾ��     imu660ra_read_registers(IMU660RA_ACC_ADDRESS, dat, 6);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void imu660ra_read_registers (uint8_t reg, uint8_t *data, uint32_t len)
{
    uint8_t temp_data[8];
    IMU660RA_CS(0);
    spi_read_8bit_registers(IMU660RA_SPI, reg | IMU660RA_SPI_R, temp_data, len + 1);
    IMU660RA_CS(1);
    for(int i = 0; i < len; i ++)
    {
        *(data ++) = temp_data[i + 1];
    }
}


//-------------------------------------------------------------------------------------------------------------------
// �������     IMU660RA �Լ�
// ����˵��     void
// ���ز���     uint8           1-�Լ�ʧ�� 0-�Լ�ɹ�
// ʹ��ʾ��     imu660ra_self_check();
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t imu660ra_self_check (void)
{
    uint8_t dat = 0, return_state = 0;
    uint16_t timeout_count = 0;
    do
    {
        if(IMU660RA_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state =  1;
            break;
        }
        dat = imu660ra_read_register(IMU660RA_CHIP_ID);
        system_delay_ms(1);
    }while(0x24 != dat);                                                        // ��ȡ�豸ID�Ƿ����0X24���������0X24����Ϊû��⵽�豸
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ IMU660RA ���ٶȼ�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     imu660ra_get_acc();                                             // ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
// ��ע��Ϣ     ʹ�� SPI �Ĳɼ�ʱ��Ϊ69us
//             ʹ�� IIC �Ĳɼ�ʱ��Ϊ126us        �ɼ����ٶȼƵ�ʱ����ɼ������ǵ�ʱ��һ�µ�ԭ���Ƕ�ֻ�Ƕ�ȡ�Ĵ�������
//-------------------------------------------------------------------------------------------------------------------
void imu660ra_get_acc (void)
{
    uint8_t dat[6];

    imu660ra_read_registers(IMU660RA_ACC_ADDRESS, dat, 6);
    imu660ra_acc_x = (int16_t)(((uint16_t)dat[1] << 8 | dat[0]));
    imu660ra_acc_y = (int16_t)(((uint16_t)dat[3] << 8 | dat[2]));
    imu660ra_acc_z = (int16_t)(((uint16_t)dat[5] << 8 | dat[4]));
}
//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ IMU660RA ����������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     imu660ra_get_gyro();                                            // ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
// ��ע��Ϣ     ʹ�� SPI �Ĳɼ�ʱ��Ϊ69us
//             ʹ�� IIC �Ĳɼ�ʱ��Ϊ126us
//-------------------------------------------------------------------------------------------------------------------
void imu660ra_get_gyro (void)
{
    uint8_t dat[6];

    imu660ra_read_registers(IMU660RA_GYRO_ADDRESS, dat, 6);
    imu660ra_gyro_x = (int16_t)(((uint16_t)dat[1] << 8 | dat[0]));
    imu660ra_gyro_y = (int16_t)(((uint16_t)dat[3] << 8 | dat[2]));
    imu660ra_gyro_z = (int16_t)(((uint16_t)dat[5] << 8 | dat[4]));
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʼ�� IMU660RA
// ����˵��     void
// ���ز���     uint8           1-��ʼ��ʧ�� 0-��ʼ���ɹ�
// ʹ��ʾ��     imu660ra_init();
// ��ע��Ϣ
//-------------------------------------------------------------------------------------------------------------------
int imu660ra_state = 0;
uint8_t imu660ra_init (void)
{
    uint8_t return_state = 0;
    system_delay_ms(20);                                                        // �ȴ��豸�ϵ�ɹ�
#if IMU660RA_USE_IIC
    #if IMU660RA_USE_SOFT_IIC
    soft_iic_init(&imu660ra_iic_struct, IMU660RA_DEV_ADDR, IMU660RA_SOFT_IIC_DELAY, IMU660RA_SCL_PIN, IMU660RA_SDA_PIN);        // ���� IMU660RA �� IIC �˿�
#else
    iic_init(IMU660RA_IIC_INDEX, IMU660RA_DEV_ADDR, IMU660RA_IIC_SPEED, IMU660RA_SCL_PIN, IMU660RA_SDA_PIN);        // ���� IMU660RA �� IIC �˿�
#endif
#else
    //spi_init(IMU660RA_SPI, SPI_MODE0, IMU660RA_SPI_SPEED, IMU660RA_SPC_PIN, IMU660RA_SDI_PIN, IMU660RA_SDO_PIN, SPI_CS_NULL);   // ���� IMU660RA �� SPI �˿�
    //gpio_init(IMU660RA_CS_PIN, GPO, GPIO_HIGH, GPO_PUSH_PULL);                  // ���� IMU660RA ��CS�˿�
    imu660ra_read_register(IMU660RA_CHIP_ID);                                   // ��ȡһ���豸ID ���豸����ΪSPIģʽ
#endif
    do{
        if(imu660ra_self_check())                                               // IMU660RA �Լ�
        {
            // �������������˶�����Ϣ ������ʾ����λ��������
            // ��ô���� IMU660RA �Լ������ʱ�˳���
            // ���һ�½�����û������ ���û������ܾ��ǻ���
            //zf_log(0, "imu660ra self check error.");
            imu660ra_state = 1;
            return_state = 1;
            break;
        }
        imu660ra_write_register(IMU660RA_PWR_CONF, 0x00);                       // �رո߼�ʡ��ģʽ
        system_delay_ms(1);
        imu660ra_write_register(IMU660RA_INIT_CTRL, 0x00);                      // ��ʼ��ģ����г�ʼ������
        imu660ra_write_registers(IMU660RA_INIT_DATA, imu660ra_config_file, sizeof(imu660ra_config_file));   // ��������ļ�
        imu660ra_write_register(IMU660RA_INIT_CTRL, 0x01);                      // ��ʼ�����ý���
        system_delay_ms(20);
        if(0 == imu660ra_read_register(IMU660RA_INT_STA))                       // ����Ƿ��������
        {
            // �������������˶�����Ϣ ������ʾ����λ��������
            // ��ô���� IMU660RA ���ó�ʼ���ļ�������
            // ���һ�½�����û������ ���û������ܾ��ǻ���
            //zf_log(0, "imu660ra init error.");
            imu660ra_state = 2;
            return_state = 1;
            break;
        }
        imu660ra_write_register(IMU660RA_PWR_CTRL, 0x0E);                       // ��������ģʽ  ʹ�������ǡ����ٶȡ��¶ȴ�����
        imu660ra_write_register(IMU660RA_ACC_CONF, 0xA7);                       // ���ٶȲɼ����� ����ģʽ �����ɼ� 50Hz  ����Ƶ��
        imu660ra_write_register(IMU660RA_GYR_CONF, 0xA9);                       // �����ǲɼ����� ����ģʽ �����ɼ� 200Hz ����Ƶ��

        // IMU660RA_ACC_SAMPLE �Ĵ���
        // ����Ϊ 0x00 ���ٶȼ�����Ϊ ��2  g   ��ȡ���ļ��ٶȼ����ݳ��� 16384  ����ת��Ϊ������λ������ ��λ g(m/s^2)
        // ����Ϊ 0x01 ���ٶȼ�����Ϊ ��4  g   ��ȡ���ļ��ٶȼ����ݳ��� 8192   ����ת��Ϊ������λ������ ��λ g(m/s^2)
        // ����Ϊ 0x02 ���ٶȼ�����Ϊ ��8  g   ��ȡ���ļ��ٶȼ����ݳ��� 4096   ����ת��Ϊ������λ������ ��λ g(m/s^2)
        // ����Ϊ 0x03 ���ٶȼ�����Ϊ ��16 g   ��ȡ���ļ��ٶȼ����ݳ��� 2048   ����ת��Ϊ������λ������ ��λ g(m/s^2)
        switch(IMU660RA_ACC_SAMPLE_DEFAULT)
        {
            default:
            {
                //zf_log(0, "IMU660RA_ACC_SAMPLE_DEFAULT set error.");
                imu660ra_state = 3;
                return_state = 1;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_2G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x00);
                imu660ra_transition_factor[0] = 16384;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_4G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x01);
                imu660ra_transition_factor[0] = 8192;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_8G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x02);
                imu660ra_transition_factor[0] = 4096;
            }break;
            case IMU660RA_ACC_SAMPLE_SGN_16G:
            {
                imu660ra_write_register(IMU660RA_ACC_RANGE, 0x03);
                imu660ra_transition_factor[0] = 2048;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }

        // IMU660RA_GYR_RANGE �Ĵ���
        // ����Ϊ 0x04 ����������Ϊ ��125  dps    ��ȡ�������������ݳ��� 262.4   ����ת��Ϊ������λ������ ��λΪ ��/s
        // ����Ϊ 0x03 ����������Ϊ ��250  dps    ��ȡ�������������ݳ��� 131.2   ����ת��Ϊ������λ������ ��λΪ ��/s
        // ����Ϊ 0x02 ����������Ϊ ��500  dps    ��ȡ�������������ݳ��� 65.6    ����ת��Ϊ������λ������ ��λΪ ��/s
        // ����Ϊ 0x01 ����������Ϊ ��1000 dps    ��ȡ�������������ݳ��� 32.8    ����ת��Ϊ������λ������ ��λΪ ��/s
        // ����Ϊ 0x00 ����������Ϊ ��2000 dps    ��ȡ�������������ݳ��� 16.4    ����ת��Ϊ������λ������ ��λΪ ��/s
        switch(IMU660RA_GYRO_SAMPLE_DEFAULT)
        {
            default:
            {
                //zf_log(0, "IMU660RA_GYRO_SAMPLE_DEFAULT set error.");
                imu660ra_state = 4;
                return_state = 1;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_125DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x04);
                imu660ra_transition_factor[1] = 262.4;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_250DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x03);
                imu660ra_transition_factor[1] = 131.2;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_500DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x02);
                imu660ra_transition_factor[1] = 65.6;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_1000DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x01);
                imu660ra_transition_factor[1] = 32.8;
            }break;
            case IMU660RA_GYRO_SAMPLE_SGN_2000DPS:
            {
                imu660ra_write_register(IMU660RA_GYR_RANGE, 0x00);
                imu660ra_transition_factor[1] = 16.4;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }
    }while(0);
    return return_state;
}
