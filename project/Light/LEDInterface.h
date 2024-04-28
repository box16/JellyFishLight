#pragma once
#include "RGB.h"

class LEDInterface
{
public:
    virtual void LightUp(const RGB &rgb) const = 0;
};
