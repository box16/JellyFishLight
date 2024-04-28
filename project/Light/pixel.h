#pragma once
#include "LEDInterface.h"

class Pixel : public LEDInterface
{
public:
    Pixel(PIO pio) : LEDInterface(pio){};
    void light_up(const RGB &rgb) const
    {
        pio_sm_put_blocking(pio_, 0, (rgb.GetGreen() << 16 | rgb.GetRed() << 8 | rgb.GetBlue()) << 8u);
    }
};