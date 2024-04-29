#pragma once
#include "RGB.h"

class ProgrammableLEDIF
{
public:
    virtual void LightUp(const RGB &rgb) const = 0;
};
