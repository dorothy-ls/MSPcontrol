#include "imu963ra.h"

int16_t imu963ra_gyro_x = 0, imu963ra_gyro_y = 0, imu963ra_gyro_z = 0;
int16_t imu963ra_acc_x = 0,  imu963ra_acc_y = 0,  imu963ra_acc_z = 0;
int16_t imu963ra_mag_x = 0,  imu963ra_mag_y = 0,  imu963ra_mag_z = 0;
float imu963ra_transition_factor[3] = {4098, 14.3, 3000};

int imu963ra_state = 0;




//-------------------------------------------------------------------------------------------------------------------
// �������     IMU963RA д�Ĵ���
// ����˵��     reg             �Ĵ�����ַ
// ����˵��     data            ����
// ���ز���     void
// ʹ��ʾ��     imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x00);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void imu963ra_write_acc_gyro_register (uint8_t reg, uint8_t data)
{
    IMU963RA_CS(0);
    spi_write_8bit_register(IMU963RA_SPI, reg | IMU963RA_SPI_W, data);

    IMU963RA_CS(1);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IMU963RA ���Ĵ���
// ����˵��     reg             �Ĵ�����ַ
// ���ز���     uint8_t           ����
// ʹ��ʾ��     imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t imu963ra_read_acc_gyro_register (uint8_t reg)
{
    uint8_t data = 0;
    IMU963RA_CS(0);
    data = spi_read_8bit_register(IMU963RA_SPI, reg | IMU963RA_SPI_R);

    IMU963RA_CS(1);
    return data;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IMU963RA ������ �ڲ�����
// ����˵��     reg             �Ĵ�����ַ
// ����˵��     data            ���ݻ�����
// ����˵��     len             ���ݳ���
// ���ز���     void
// ʹ��ʾ��     imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_A, dat, 6);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void imu963ra_read_acc_gyro_registers (uint8_t reg, uint8_t *data, uint32_t len)
{
    IMU963RA_CS(0);
    spi_read_8bit_registers(IMU963RA_SPI, reg | IMU963RA_SPI_R, data, len);

    IMU963RA_CS(1);
}


//-------------------------------------------------------------------------------------------------------------------
// �������     IMU963RA ��Ϊ IIC �����������д����
// ����˵��     addr            Ŀ���ַ
// ����˵��     reg             Ŀ��Ĵ���
// ����˵��     data            ����
// ���ز���     uint8_t           1-ʧ�� 0-�ɹ�
// ʹ��ʾ��     imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL2, 0x80);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t imu963ra_write_mag_register (uint8_t addr, uint8_t reg, uint8_t data)
{
    uint8_t return_state = 0;
    uint16_t timeout_count = 0;

    addr = addr << 1;
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x00);               // �ӻ�0�������
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 0);              // ���õشżƵ�ַ��ע��������Ҫ����8λ��I2C��ַ�� 0x2C
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);                // ��Ҫд��ļĴ�����ַ
    imu963ra_write_acc_gyro_register(IMU963RA_DATAWRITE_SLV0, data);            // ��Ҫд�������
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x4C);             // ���ڵ�һ����������ͨѶ �������� I2C����ʹ��
    
    // �ȴ�ͨѶ�ɹ�
    while(0 == (0x80 & imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER)))
    {
        if(IMU963RA_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state = 1;
            break;
        }
        system_delay_ms(2);
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IMU963RA ��Ϊ IIC ����������ƶ�����
// ����˵��     addr            Ŀ���ַ
// ����˵��     reg             Ŀ��Ĵ���
// ���ز���     uint8_t           ��ȡ������
// ʹ��ʾ��     imu963ra_read_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CHIP_ID);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t imu963ra_read_mag_register (uint8_t addr, uint8_t reg)
{
    uint16_t timeout_count = 0;

    addr = addr << 1;
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 1);              // ���õشżƵ�ַ��ע��������Ҫ����8λ��I2C��ַ�� 0x2C
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);                // ��Ҫ��ȡ�ļĴ�����ַ
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x01);    
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x4C);             // ���ڵ�һ����������ͨѶ �������� I2C����ʹ��
    
    // �ȴ�ͨѶ�ɹ�
    while(0 == (0x01 & imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER)))
    {
        if(IMU963RA_TIMEOUT_COUNT < timeout_count ++)
        {
            break;
        }
        system_delay_ms(2);
    }
    
    return (imu963ra_read_acc_gyro_register(IMU963RA_SENSOR_HUB_1));            // ���ض�ȡ��������
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IMU963RA ��Ϊ IIC ������������Զ�д����
// ����˵��     addr            Ŀ���ַ
// ����˵��     reg             Ŀ��Ĵ���
// ���ز���     void
// ʹ��ʾ��     imu963ra_connect_mag(IMU963RA_MAG_ADDR, IMU963RA_MAG_OUTX_L);
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static void imu963ra_connect_mag (uint8_t addr, uint8_t reg)
{
    addr = addr << 1;
    
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_ADD, addr | 1);              // ���õشżƵ�ַ��ע��������Ҫ����8λ��I2C��ַ�� 0x2C
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_SUBADD, reg);                // ��Ҫ��ȡ�ļĴ�����ַ
    imu963ra_write_acc_gyro_register(IMU963RA_SLV0_CONFIG, 0x06);    
    imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x6C);             // ���ڵ�һ����������ͨѶ �������� I2C����ʹ��
}   


//-------------------------------------------------------------------------------------------------------------------
// �������     IMU963RA �����Լ� �ڲ�����
// ����˵��     void
// ���ز���     uint8_t           1-�Լ�ʧ�� 0-�Լ�ɹ�
// ʹ��ʾ��     imu963ra_acc_gyro_self_check();
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t imu963ra_acc_gyro_self_check (void)
{
    uint8_t return_state = 0;
    uint8_t dat = 0;
    uint16_t timeout_count = 0;

    while(0x6B != dat)                                                          // �ж� ID �Ƿ���ȷ
    {
        if(IMU963RA_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state = 1;
            break;
        }
        dat = imu963ra_read_acc_gyro_register(IMU963RA_WHO_AM_I);
        system_delay_ms(10);
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     IMU963RA �������Լ� �ڲ�����
// ����˵��     void
// ���ز���     uint8_t           1-�Լ�ʧ�� 0-�Լ�ɹ�
// ʹ��ʾ��     imu963ra_mag_self_check();
// ��ע��Ϣ     �ڲ�����
//-------------------------------------------------------------------------------------------------------------------
static uint8_t imu963ra_mag_self_check (void)
{
    uint8_t return_state = 0;
    uint8_t dat = 0;
    uint16_t timeout_count = 0;

    while(0xff != dat)                                                          // �ж� ID �Ƿ���ȷ
    {
        if(IMU963RA_TIMEOUT_COUNT < timeout_count ++)
        {
            return_state = 1;
            break;
        }
        dat = imu963ra_read_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CHIP_ID);
        system_delay_ms(10);
    }
    return return_state;
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ IMU963RA ���ٶȼ�����
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     imu963ra_get_acc();
// ��ע��Ϣ     ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_get_acc (void)
{
    uint8_t dat[6];

    imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_A, dat, 6);
    imu963ra_acc_x = (int16_t)(((uint16_t)dat[1] << 8 | dat[0]));
    imu963ra_acc_y = (int16_t)(((uint16_t)dat[3] << 8 | dat[2]));
    imu963ra_acc_z = (int16_t)(((uint16_t)dat[5] << 8 | dat[4]));
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡIMU963RA����������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     imu963ra_get_gyro();
// ��ע��Ϣ     ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_get_gyro (void)
{
    uint8_t dat[6];

    imu963ra_read_acc_gyro_registers(IMU963RA_OUTX_L_G, dat, 6);
    imu963ra_gyro_x = (int16_t)(((uint16_t)dat[1] << 8 | dat[0]));
    imu963ra_gyro_y = (int16_t)(((uint16_t)dat[3] << 8 | dat[2]));
    imu963ra_gyro_z = (int16_t)(((uint16_t)dat[5] << 8 | dat[4]));
}


//-------------------------------------------------------------------------------------------------------------------
// �������     ��ȡ IMU963RA ����������
// ����˵��     void
// ���ز���     void
// ʹ��ʾ��     imu963ra_get_mag();
// ��ע��Ϣ     ִ�иú�����ֱ�Ӳ鿴��Ӧ�ı�������
//-------------------------------------------------------------------------------------------------------------------
void imu963ra_get_mag (void)
{
    uint8_t temp_status;
    uint8_t dat[6];

    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x40);
    temp_status = imu963ra_read_acc_gyro_register(IMU963RA_STATUS_MASTER);
    if(0x01 & temp_status)
    {
        imu963ra_read_acc_gyro_registers(IMU963RA_SENSOR_HUB_1, dat, 6);
        imu963ra_mag_x = (int16_t)(((uint16_t)dat[1] << 8 | dat[0]));
        imu963ra_mag_y = (int16_t)(((uint16_t)dat[3] << 8 | dat[2]));
        imu963ra_mag_z = (int16_t)(((uint16_t)dat[5] << 8 | dat[4]));
    }
    imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);
}

//-------------------------------------------------------------------------------------------------------------------
// �������     ��ʼ�� IMU963RA
// ����˵��     void
// ���ز���     uint8_t           1-��ʼ��ʧ�� 0-��ʼ���ɹ�
// ʹ��ʾ��     imu963ra_init();
// ��ע��Ϣ     
//-------------------------------------------------------------------------------------------------------------------
uint8_t imu963ra_init (void)
{
    uint8_t return_state = 0;
    system_delay_ms(10);                                                        // �ϵ���ʱ


    do
    {
        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);       // �ر�HUB�Ĵ�������
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL3_C, 0x01);               // ��λ�豸
        system_delay_ms(2);                             
        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);       // �ر�HUB�Ĵ�������
        if(imu963ra_acc_gyro_self_check())                   
        {                   
            //zf_log(0, "IMU963RA acc and gyro self check error.");
            imu963ra_state = 1;
            return_state = 1;
            break;            
        }                   
                            
        imu963ra_write_acc_gyro_register(IMU963RA_INT1_CTRL, 0x03);             // ���������� ���ٶ����ݾ����ж�

        // IMU963RA_CTRL1_XL �Ĵ���
        // ����Ϊ 0x30 ���ٶ�����Ϊ ��2  G    ��ȡ���ļ��ٶȼ����ݳ��� 16393  ����ת��Ϊ��������λ������ ��λ g(m/s^2)
        // ����Ϊ 0x38 ���ٶ�����Ϊ ��4  G    ��ȡ���ļ��ٶȼ����ݳ��� 8197   ����ת��Ϊ��������λ������ ��λ g(m/s^2)
        // ����Ϊ 0x3C ���ٶ�����Ϊ ��8  G    ��ȡ���ļ��ٶȼ����ݳ��� 4098   ����ת��Ϊ��������λ������ ��λ g(m/s^2)
        // ����Ϊ 0x34 ���ٶ�����Ϊ ��16 G    ��ȡ���ļ��ٶȼ����ݳ��� 2049   ����ת��Ϊ��������λ������ ��λ g(m/s^2)
        switch(IMU963RA_ACC_SAMPLE_DEFAULT)
        {
            default:
            {
                //zf_log(0, "IMU963RA_ACC_SAMPLE_DEFAULT set error.");
                imu963ra_state = 2;
                return_state = 1;
            }break;
            case IMU963RA_ACC_SAMPLE_SGN_2G:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x30);
                imu963ra_transition_factor[0] = 16393;
            }break;
            case IMU963RA_ACC_SAMPLE_SGN_4G:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x38);
                imu963ra_transition_factor[0] = 8197;
            }break;
            case IMU963RA_ACC_SAMPLE_SGN_8G:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x3C);
                imu963ra_transition_factor[0] = 4098;
            }break;
            case IMU963RA_ACC_SAMPLE_SGN_16G:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL1_XL, 0x34);
                imu963ra_transition_factor[0] = 2049;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }

        // IMU963RA_CTRL2_G �Ĵ���
        // ����Ϊ 0x52 ����������Ϊ ��125  dps    ��ȡ�������������ݳ��� 228.6   ����ת��Ϊ��������λ������ ��λΪ ��/s
        // ����Ϊ 0x50 ����������Ϊ ��250  dps    ��ȡ�������������ݳ��� 114.3   ����ת��Ϊ��������λ������ ��λΪ ��/s
        // ����Ϊ 0x54 ����������Ϊ ��500  dps    ��ȡ�������������ݳ��� 57.1    ����ת��Ϊ��������λ������ ��λΪ ��/s
        // ����Ϊ 0x58 ����������Ϊ ��1000 dps    ��ȡ�������������ݳ��� 28.6    ����ת��Ϊ��������λ������ ��λΪ ��/s
        // ����Ϊ 0x5C ����������Ϊ ��2000 dps    ��ȡ�������������ݳ��� 14.3    ����ת��Ϊ��������λ������ ��λΪ ��/s
        // ����Ϊ 0x51 ����������Ϊ ��4000 dps    ��ȡ�������������ݳ��� 7.1     ����ת��Ϊ��������λ������ ��λΪ ��/s
        switch(IMU963RA_GYRO_SAMPLE_DEFAULT)
        {
            default:
            {
                //zf_log(0, "IMU963RA_GYRO_SAMPLE_DEFAULT set error.");
                imu963ra_state = 3;
                return_state = 1;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_125DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x52);
                imu963ra_transition_factor[1] = 228.6;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_250DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x50);
                imu963ra_transition_factor[1] = 114.3;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_500DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x54);
                imu963ra_transition_factor[1] = 57.1;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_1000DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x58);
                imu963ra_transition_factor[1] = 28.6;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_2000DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x5C);
                imu963ra_transition_factor[1] = 14.3;
            }break;
            case IMU963RA_GYRO_SAMPLE_SGN_4000DPS:
            {
                imu963ra_write_acc_gyro_register(IMU963RA_CTRL2_G, 0x51);
                imu963ra_transition_factor[1] = 7.1;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }

        imu963ra_write_acc_gyro_register(IMU963RA_CTRL3_C, 0x44);               // ʹ�����������ֵ�ͨ�˲���
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL4_C, 0x02);               // ʹ�����ֵ�ͨ�˲���
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL5_C, 0x00);               // ���ٶȼ�����������������
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL6_C, 0x00);               // �������ٶȼƸ�����ģʽ �����ǵ�ͨ�˲� 133hz
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL7_G, 0x00);               // ���������Ǹ�����ģʽ �رո�ͨ�˲�
        imu963ra_write_acc_gyro_register(IMU963RA_CTRL9_XL, 0x01);              // �ر�I3C�ӿ�

        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x40);       // ����HUB�Ĵ������� �������õشż�
        imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x80);         // ��λI2C����
        system_delay_ms(2);                             
        imu963ra_write_acc_gyro_register(IMU963RA_MASTER_CONFIG, 0x00);         // �����λ��־
        system_delay_ms(2);
        
        imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL2, 0x80);// ��λ���ӵ�����
        system_delay_ms(2);
        imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL2, 0x00);
        system_delay_ms(2);

        if(imu963ra_mag_self_check())
        {
            //zf_log(0, "IMU963RA mag self check error.");
            imu963ra_state = 4;
            return_state = 1;
            break;            
        }

        // IMU963RA_MAG_ADDR �Ĵ���
        // ����Ϊ 0x09 ����������Ϊ 2G   ��ȡ���Ĵ��������ݳ��� 12000   ����ת��Ϊ��������λ������ ��λ G(��˹)
        // ����Ϊ 0x19 ����������Ϊ 8G   ��ȡ���Ĵ��������ݳ��� 3000    ����ת��Ϊ��������λ������ ��λ G(��˹)
        switch(IMU963RA_MAG_SAMPLE_DEFAULT)
        {
            default:
            {
                //zf_log(0, "IMU963RA_MAG_SAMPLE_DEFAULT set error.");
                imu963ra_state = 5;
                return_state = 1;
            }break;
            case IMU963RA_MAG_SAMPLE_2G:
            {
                imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL1, 0x09);
                imu963ra_transition_factor[2] = 12000;
            }break;
            case IMU963RA_MAG_SAMPLE_8G:
            {
                imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_CONTROL1, 0x19);
                imu963ra_transition_factor[2] = 3000;
            }break;
        }
        if(1 == return_state)
        {
            break;
        }

        imu963ra_write_mag_register(IMU963RA_MAG_ADDR, IMU963RA_MAG_FBR, 0x01);
        imu963ra_connect_mag(IMU963RA_MAG_ADDR, IMU963RA_MAG_OUTX_L);
        
        imu963ra_write_acc_gyro_register(IMU963RA_FUNC_CFG_ACCESS, 0x00);       // �ر�HUB�Ĵ�������

        system_delay_ms(20);                                                    // �ȴ������ƻ�ȡ����
    }while(0);
    return return_state;
}