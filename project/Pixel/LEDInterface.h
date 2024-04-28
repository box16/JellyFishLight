#pragma once
#include "hardware/pio.h"
#include "RGB/RGB.h"

class LEDInterface
{
public:
    LEDInterface(const PIO &pio) : pio_(pio){};
    virtual void light_up(const RGB &color_code) const = 0;

protected:
    PIO pio_;
};
