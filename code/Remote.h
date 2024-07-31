#ifndef CONTROL_REMOTE_H
#define CONTROL_REMOTE_H

#include "hal.h"

typedef enum{
    REMOTE_DISCONNECTED=0,
    REMOTE_CONNECTED
} remote_state;

class Remote {
public:
    remote_state state = REMOTE_DISCONNECTED;

    uint16_t data[100];
    uint16_t len = 0;

    int mode = 0;
    float horizontal = 0; //-1 - 1
    float vertical = 0; //-1 - 1

    Remote(UART_Regs *huart);

    void Handler();
    void process_data(); //Ω” ’÷–∂œ

private:
    UART_Regs *huart;

};

#endif
