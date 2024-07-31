#ifndef CONTROL_BUZZER_H
#define CONTROL_BUZZER_H

#include "hal.h"

class Buzzer{
public:
    void start();
    void stop();
    Buzzer(GPTIMER_Regs *htim);

private:
    GPTIMER_Regs *htim;

};

#endif
