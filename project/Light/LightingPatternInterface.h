#pragma once
#include "LEDInterface.h"
#include "RGB.h"
#include <vector>
class LightingPatternInterface
{
public:
    virtual std::vector<RGB> LightUp(const LEDInterface &led_interface,
                                     const uint len,
                                     const uint time) const = 0;
};
