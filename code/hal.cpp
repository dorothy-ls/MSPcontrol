#include "hal.h"
//HAL_SPI_Transmit(hspi, &temp, 1, 0xffff);
void SPI_transmitData(SPI_Regs *hspi, uint8_t *data, uint8_t dataLength)
{
    int i = 0;
    for (i = 0; i < dataLength; i++) {
        while (DL_SPI_isBusy(hspi))
            ;
        DL_SPI_transmitData8(hspi, data[i]);
    }
    while (DL_SPI_isBusy(hspi));
}
//HAL_SPI_Receive(hspi, &temp, 1, 0xffff);
void SPI_receiveData(SPI_Regs *hspi, uint8_t *data, uint8_t dataLength)
{
    int i = 0;
    for (i = 0; i < dataLength; i++) {
        DL_SPI_transmitData8(hspi,0xff);
        while (DL_SPI_isBusy(hspi));
        while (!DL_SPI_isRXFIFOEmpty(hspi))
         data[i] = DL_SPI_receiveData8(hspi);
    }
}


void spi_write_8bit_register(SPI_Regs *hspi, uint8_t reg, uint8_t data){
    uint8_t temp = reg;
    //HAL_SPI_Transmit(hspi, &temp, 1, 0xffff);
    SPI_transmitData(hspi, &temp, 1);
    temp = data;
    //HAL_SPI_Transmit(hspi, &temp, 1, 0xffff);
    SPI_transmitData(hspi, &temp, 1);
}

void spi_write_8bit_registers(SPI_Regs *hspi, uint8_t reg, uint8_t* data, uint16_t len){
    uint8_t temp = reg;
    //HAL_SPI_Transmit(hspi, &temp, 1, 0xffff);
    SPI_transmitData(hspi, &temp, 1);
    //HAL_SPI_Transmit(hspi, data, len, 0xffff);
    SPI_transmitData(hspi, data, len);
}

//void spi_read_8bit_registers(SPI_Regs *hspi, uint8_t reg, uint8_t* data, uint16_t len){
//    uint8_t temp = reg;
//    //HAL_SPI_Transmit(hspi, &temp, 1, 0xffff);
//    SPI_transmitData(hspi, &temp, 1);
//    //HAL_SPI_Receive(hspi, data, len, 0xffff);
//    SPI_receiveData(hspi, data, len);
//
//}

//uint8_t spi_read_8bit_register(SPI_Regs *hspi, uint8_t reg){
//    uint8_t temp;
//    //HAL_SPI_Transmit(hspi, &temp, 1, 0xffff);
//    SPI_transmitData(hspi, &reg, 1);
//    //HAL_SPI_Receive(hspi, &temp, 1, 0xffff);
//    //SPI_transmitData(hspi, &temp, 1);
//    SPI_receiveData(hspi, &temp, 1);
//
//    return temp;
//}


void spi_read_8bit_registers(SPI_Regs *hspi, uint8_t reg, uint8_t *data, uint16_t len){
    DL_SPI_transmitData8(hspi,reg);
    while (DL_SPI_isBusy(hspi));
    for (int i = 0; i< len; i++) {
        DL_SPI_transmitData8(hspi,0);
        while (DL_SPI_isBusy(hspi));
        while (!DL_SPI_isRXFIFOEmpty(hspi))
            data[i] = DL_SPI_receiveData8(hspi);
    }
}
//
uint8_t spi_read_8bit_register(SPI_Regs *hspi, uint8_t reg){
    DL_SPI_transmitData8(hspi,reg);
    while (DL_SPI_isBusy(hspi));
    DL_SPI_transmitData8(hspi,0);
    while (DL_SPI_isBusy(hspi));
    uint8_t data = 0;
    while (!DL_SPI_isRXFIFOEmpty(hspi))
        data = DL_SPI_receiveData8(hspi);
    return data;
}
