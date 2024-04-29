#pragma once
#include "RGB.h"
#include <vector>

class LightingPatternIF
{
public:
    virtual std::vector<RGB> Next(const uint led_num) = 0;
    virtual void Initialize() = 0;
};
