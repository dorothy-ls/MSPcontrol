#ifdef __cplusplus
extern "C" {
#endif

#include "ti_msp_dl_config.h"
#include "it.h"
#include "config.h"
#include "stdio.h"
int fputc(int ch, FILE *f);
	
#define system_delay_ms delay_ms
void SPI_transmitData(SPI_Regs *hspi, uint8_t *data, uint16_t dataLength);
void SPI_receiveData(SPI_Regs *hspi, uint8_t *data, uint16_t dataLength);
void spi_write_8bit_register(SPI_Regs *hspi, uint8_t reg, uint8_t data);
void spi_write_8bit_registers(SPI_Regs *hspi, uint8_t reg, uint8_t* data, uint16_t len);
uint8_t spi_read_8bit_register(SPI_Regs *hspi, uint8_t reg);
void spi_read_8bit_registers(SPI_Regs *hspi, uint8_t reg, uint8_t* data, uint16_t len);
	
#ifdef __cplusplus
}
#endif
