#pragma once
#include "LEDInterface.h"
#include "RGB.h"
#include <vector>
class LightingPatternInterface
{
public:
    virtual std::vector<RGB> Next(const uint led_num) = 0;
    virtual void Initialize() = 0;
};
