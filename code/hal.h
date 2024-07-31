#ifndef HAL_H
#define HAL_H

#ifdef __cplusplus
extern "C" {
#endif


#include "ti_msp_dl_config.h"
#include "it.h"
#include "config.h"
#include "stdio.h"
int fputc(int ch, FILE *f);

#define huart1 UART_0_INST
void HAL_UART_Transmit(UART_Regs *uart,uint8_t *data, uint16_t len, uint32_t timeout);

#define system_delay_ms delay_ms

void HAL_SPI_Transmit(SPI_Regs *hspi, uint8_t *data, uint8_t dataLength, uint32_t timeout);
void HAL_SPI_Receive(SPI_Regs *hspi, uint8_t *data, uint8_t dataLength, uint32_t timeout);
void spi_write_8bit_register(SPI_Regs *hspi, uint8_t reg, uint8_t data);
void spi_write_8bit_registers(SPI_Regs *hspi, uint8_t reg, uint8_t* data, uint16_t len);
uint8_t spi_read_8bit_register(SPI_Regs *hspi, uint8_t reg);
void spi_read_8bit_registers(SPI_Regs *hspi, uint8_t reg, uint8_t* data, uint16_t len);
	
#ifdef __cplusplus
}
#endif

#endif