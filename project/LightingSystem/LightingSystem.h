#pragma once
#include "Pixel/LEDInterface.h"
class LightPatternInterface
{
public:
    virtual void light_up(const LEDInterface &led_interface,
                          const uint len,
                          const uint time) const = 0;
};
