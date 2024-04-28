#pragma once
#include "hardware/pio.h"
#include "RGB.h"

class LEDInterface
{
public:
    virtual void LightUp(const RGB &rgb) const = 0;
};
