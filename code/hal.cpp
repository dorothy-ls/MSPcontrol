#include "hal.h"

void HAL_UART_Transmit(UART_Regs *uart,uint8_t *data, uint16_t len, uint32_t timeout)
{
    int i = 0;
	uint32_t tick = utick;
    for(i = 0; i < len; i++)
    {
        while( DL_UART_isBusy(uart) == true && utick - tick < timeout);
		if(utick - tick >= timeout) return;
        DL_UART_transmitData(uart,data[i]);
    }
}

int fputc(int ch, FILE *f)
{
    HAL_UART_Transmit(huart1, (uint8_t*)&ch, 1, 0xff);
    return ch;
}
//HAL_SPI_Transmit(hspi, &temp, 1, 0xffff);
void HAL_SPI_Transmit(SPI_Regs *hspi, uint8_t *data, uint8_t dataLength, uint32_t timeout)
{
    int i = 0;
	uint32_t tick = utick;
    for (i = 0; i < dataLength; i++) {
        while (DL_SPI_isBusy(hspi) && utick - tick < timeout)
            ;
		if(utick - tick >= timeout) return;
        DL_SPI_transmitData8(hspi, data[i]);
    }
}
//HAL_SPI_Receive(hspi, &temp, 1, 0xffff);
void HAL_SPI_Receive(SPI_Regs *hspi, uint8_t *data, uint8_t dataLength, uint32_t timeout)
{
    int i = 0;
	uint32_t tick = utick;
    while (DL_SPI_isBusy(hspi) && utick - tick < timeout)
        ;
    if(utick - tick >= timeout) return;
    for (i = 0; i < dataLength; i++) {
        DL_SPI_transmitData8(hspi,0xff);
        while (DL_SPI_isBusy(hspi) && utick - tick < timeout)
            ;
        while (DL_SPI_isRXFIFOEmpty(hspi) && utick - tick < timeout)
			;
		if(utick - tick >= timeout) return;
        data[i] = DL_SPI_receiveData8(hspi);
    }
}

void spi_write_8bit_register(SPI_Regs *hspi, uint8_t reg, uint8_t data){
    uint8_t temp = reg;
    HAL_SPI_Transmit(hspi, &temp, 1, 0xff);
    temp = data;
    HAL_SPI_Transmit(hspi, &temp, 1, 0xff);
}

void spi_write_8bit_registers(SPI_Regs *hspi, uint8_t reg, uint8_t* data, uint16_t len){
    uint8_t temp = reg;
    HAL_SPI_Transmit(hspi, &temp, 1, 0xff);
    HAL_SPI_Transmit(hspi, data, len, 0xffff);
}

//uint8_t spi_read_8bit_register(SPI_Regs *hspi, uint8_t reg){
//    uint8_t temp = reg;
//    HAL_SPI_Transmit(hspi, &temp, 1, 0xff);
//    HAL_SPI_Receive(hspi, &temp, 1, 0xff);
//    return temp;
//}
//
//void spi_read_8bit_registers(SPI_Regs *hspi, uint8_t reg, uint8_t* data, uint16_t len){
//    uint8_t temp = reg;
//    HAL_SPI_Transmit(hspi, &temp, 1, 0xff);
//    HAL_SPI_Receive(hspi, data, len, 0xff);
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
