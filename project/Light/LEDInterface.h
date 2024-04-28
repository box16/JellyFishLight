#pragma once
#include "hardware/pio.h"
#include "RGB.h"

class LEDInterface
{
public:
    virtual void light_up(const RGB &rgb) const = 0;
};
