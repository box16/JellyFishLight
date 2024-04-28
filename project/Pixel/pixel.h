#pragma once

#include "LEDInterface.h"

class Pixel : public LEDInterface
{
public:
    Pixel(PIO pio) : LEDInterface(pio){};
    void light_up(const RGB &color_code) const
    {
        pio_sm_put_blocking(pio_, 0, color_code.GRB() << 8u);
    }
};