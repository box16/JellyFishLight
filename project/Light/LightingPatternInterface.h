#pragma once
#include "LEDInterface.h"

class LightingPatternInterface
{
public:
    virtual void LightUp(const LEDInterface &led_interface,
                         const uint len,
                         const uint time) const = 0;
};
