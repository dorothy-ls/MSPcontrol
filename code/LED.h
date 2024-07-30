#ifndef CONTROL_LED_H
#define CONTROL_LED_H

class controlGPIOPin
{
   public:
    controlGPIOPin(GPIO_Regs* gpio, uint32_t pins)
    {
        gpioPort = gpio;
        gpioPins = pins;
    }
    void clear(void)
    {
        DL_GPIO_clearPins(gpioPort, gpioPins);
    }
    void set(void)
    {
        DL_GPIO_setPins(gpioPort, gpioPins);
    }
    void toggle(void)
    {
        DL_GPIO_togglePins(gpioPort, gpioPins);
    }

   private:
    GPIO_Regs* gpioPort;
    uint32_t gpioPins;
};

#endif
