#include "LS7366R.h"


// Constructors ////////////////////////////////////////////////////////////////

LS7366R::LS7366R(SPI_Regs *_spi_inst, GPIO_Regs * _si_port, uint32_t _leftSelect, uint32_t _rightSelect)
{
    leftSelect = _leftSelect;
    rightSelect = _rightSelect;
    si_port = _si_port;
    spi_inst = _spi_inst;

}


void LS7366R::init(unsigned char mdr0_conf, unsigned char mdr1_conf)
{
    uint8_t temp;
//    pinMode(leftSelect, OUTPUT);
//    pinMode(rightSelect, OUTPUT);
//    SPI.begin();

    temp = WR | MDR0;
    //digitalWrite(leftSelect, LOW);
    DL_GPIO_clearPins(si_port,leftSelect);
    //SPI.transfer(WR | MDR0);
    //SPI.transfer(mdr0_conf);

    HAL_SPI_Transmit(spi_inst, &temp, 1, 0xff);
    HAL_SPI_Transmit(spi_inst, &mdr0_conf, 1, 0xff);
    DL_GPIO_setPins(si_port,leftSelect);

    temp = WR | MDR1;
    DL_GPIO_clearPins(si_port,leftSelect);

    HAL_SPI_Transmit(spi_inst, &temp, 1, 0xff);
    HAL_SPI_Transmit(spi_inst, &mdr1_conf, 1, 0xff);
    DL_GPIO_setPins(si_port,leftSelect);

    temp = WR | MDR0;
    DL_GPIO_clearPins(si_port,rightSelect);

    HAL_SPI_Transmit(spi_inst, &temp, 1, 0xff);
    HAL_SPI_Transmit(spi_inst, &mdr0_conf, 1, 0xff);
    DL_GPIO_setPins(si_port,rightSelect);

    temp = WR | MDR1;
    DL_GPIO_clearPins(si_port,rightSelect);

    HAL_SPI_Transmit(spi_inst, &temp, 1, 0xff);
    HAL_SPI_Transmit(spi_inst, &mdr1_conf, 1, 0xff);
    DL_GPIO_setPins(si_port,rightSelect);

    reset();
    LSR=7;
}

// Public Methods //////////////////////////////////////////////////////////////

void LS7366R::reset()
{
    uint8_t temp = CLR | CNTR;
    DL_GPIO_clearPins(si_port,leftSelect);
    DL_GPIO_clearPins(si_port,rightSelect);
    HAL_SPI_Transmit(spi_inst, &temp, 1, 0xff);
    DL_GPIO_setPins(si_port,leftSelect);
    DL_GPIO_setPins(si_port,rightSelect);
}

void LS7366R::Handler()
{



    uint8_t temp;

    temp = LOAD | OTR;
    DL_GPIO_clearPins(si_port,leftSelect);
    DL_GPIO_clearPins(si_port,rightSelect);
    HAL_SPI_Transmit(spi_inst, &temp, 1, 0xff);
    DL_GPIO_setPins(si_port,leftSelect);
    DL_GPIO_setPins(si_port,rightSelect);

    temp = RD | OTR;
    DL_GPIO_clearPins(si_port,leftSelect);
//    SPI.transfer(RD | OTR);

//    HAL_SPI_Transmit(spi_inst, &temp, 1);
//    HAL_SPI_Receive(spi_inst, count1, 4);
    spi_read_8bit_registers(spi_inst,temp,count1,4);
//    count = SPI.transfer(0x00);
//    count <<= 8;
//    count |= SPI.transfer(0x00);
//    count <<= 8;
//    count |= SPI.transfer(0x00);
//    count <<= 8;
//    count |= SPI.transfer(0x00);
    DL_GPIO_setPins(si_port,leftSelect);

    for(int i = 0; i < 4; i++){
        temp_data[3 - i] = count1[i];
    }
    leftValue = *(uint32_t*)temp_data;
    //leftValue = (count1[0] << 24) + (count1[1] << 16) + (count1[2] << 8) + count1[3];

    temp = RD | OTR;
    DL_GPIO_clearPins(si_port,rightSelect);
//    SPI.transfer(RD | OTR);

//    HAL_SPI_Transmit(spi_inst, &temp, 1);
//    HAL_SPI_Receive(spi_inst, count2, 4);
    spi_read_8bit_registers(spi_inst,temp,count2,4);
//    count = SPI.transfer(0x00);
//    count <<= 8;
//    count |= SPI.transfer(0x00);
//    count <<= 8;
//    count |= SPI.transfer(0x00);
//    count <<= 8;
//    count |= SPI.transfer(0x00);
    DL_GPIO_setPins(si_port,rightSelect);

    for(int i = 0; i < 4; i++){
        temp_data[3 - i] = count2[i];
    }
    rightValue = *(uint32_t*)temp_data;
    //rightValue = (count2[0] << 24) + (count2[1] << 16) + (count2[2] << 8) + count2[3];
}

long LS7366R::left()
{
    return leftValue;
}

long LS7366R::right()
{
    return rightValue;
}
