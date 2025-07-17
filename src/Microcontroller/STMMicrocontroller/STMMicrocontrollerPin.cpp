#include "STMMicrocontrollerPin.h"


STMMicrocontrollerPin::STMMicrocontrollerPin(GPIO_TypeDef* gpio, uint16_t pin)
{
    _gpio = gpio;
    _pin = pin;
}

bool STMMicrocontrollerPin::Read()
{
    return (_gpio->IDR & _pin) != 0;
}

void STMMicrocontrollerPin::Write(bool value)
{
    if (value)
    {
        _gpio->BSRR = _pin;

    }
    else {
        _gpio->BRR = _pin;
    }
}
