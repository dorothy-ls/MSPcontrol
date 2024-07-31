#ifndef CONTROL_LED_H
#define CONTROL_LED_H

#include "hal.h"

class controlGPIOPin
{
public:
    controlGPIOPin(GPIO_Regs* gpio, uint32_t pins)
    {
        gpioPort = gpio;
        gpioPins = pins;
    }
    inline void clear(void)
    {
        DL_GPIO_clearPins(gpioPort, gpioPins);
    }
    inline void set(void)
    {
        DL_GPIO_setPins(gpioPort, gpioPins);
    }
    inline void toggle(void)
    {
        DL_GPIO_togglePins(gpioPort, gpioPins);
    }

private:
    GPIO_Regs* gpioPort;
    uint32_t gpioPins;
};

#endif
