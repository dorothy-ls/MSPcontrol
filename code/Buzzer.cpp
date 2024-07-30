#include "Buzzer.h"



Buzzer::Buzzer(GPTIMER_Regs *htim)
{
    this->htim = htim;
}

void Buzzer::start()
{
    DL_Timer_startCounter(htim);
}

void Buzzer::stop()
{
    DL_Timer_stopCounter(htim);
}
