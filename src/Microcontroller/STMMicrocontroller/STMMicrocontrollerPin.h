#pragma once
#include "MicrocontrollerPin.h"
#include <cstdint>
#include "GPIO_TypeDef.h"

class STMMicrocontrollerPin :
    public MicrocontrollerPin
{
private:
    GPIO_TypeDef* _gpio;
    uint16_t _pin;

public:
    STMMicrocontrollerPin(GPIO_TypeDef* gpio, uint16_t pin);

    bool Read() override;
    void Write(bool value) override;
};

