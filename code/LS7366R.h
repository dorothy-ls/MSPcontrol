#ifndef CONTROL_LS7366R_H
#define CONTROL_LS7366R_H

#include "hal.h"

#define CLR 0B00000000
#define RD 0B01000000
#define WR 0B10000000
#define LOAD 0B11000000

#define MDR0 0B00001000
#define MDR1 0B00010000
#define DTR 0B00011000
#define CNTR 0B00100000
#define OTR 0B00101000
#define STR 0B00110000

// filter factor 1
// async index
// no index
// free-running
// 4x quadrature
#define MDR0_CONF 0B00000011

// no flag
// enabled
// 32 bits
#define MDR1_CONF 0B00000000

class LS7366R {
    public:
        GPIO_Regs *si_port;
        uint32_t leftSelect;
        uint32_t rightSelect;

        SPI_Regs *spi_inst;

        uint32_t leftValue;
        uint32_t rightValue;

        LS7366R(SPI_Regs *_spi_inst, GPIO_Regs *_si_port, uint32_t _leftSelect, uint32_t _rightSelect);
        void init(unsigned char mdr0_conf, unsigned char mdr1_conf);
        void reset();
        void Handler();
        long left();
        long right();

private:
    uint8_t count1[4];
    uint8_t count2[4];
    uint32_t LSR = 0;
    uint8_t temp_data[4];
};

#endif
