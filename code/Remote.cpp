#include "Remote.h"

extern uint8_t* uart1_rx_buf;
#define REMOTE_LEN 3

uint32_t remote_cnt = 0;
uint16_t crc;
uint16_t crc1 = 0;
int crc_err = 0;

void Remote::process_data()
{
    if(len == REMOTE_LEN * 2 + 2 + 2)
    {//��������
        uint16_t mode = data[0];
        float vertical = (float)(data[2] - 2048) / 2048 * 1 - 0.07;
        float horizontal = (float)(data[1] - 2048) / 2048 * 1 - 0.07;
        crc = data[3];
        crc1 = 0;
        for(int i = 0; i < REMOTE_LEN; i++) crc1 += data[i];
        remote_cnt++;
        crc_err = crc1 - crc;
        if(mode <= 2 && data[1] < 4096 && data[2] < 4096 && crc1 == crc)
        {
            this->mode = mode;
            this->vertical = -vertical * 0.1 + this->vertical * 0.9;
            this->horizontal = -horizontal * 0.1 + this->horizontal * 0.9;
        }
    }
}

Remote::Remote(UART_Regs *huart) {
    this->huart = huart;
}

void Remote::Handler() {
    state = REMOTE_CONNECTED;
    process_data();
}
