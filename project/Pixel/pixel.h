#pragma once

#include "LightingSystem/LightingSystem.h"
#include "hardware/pio.h"

class Pixel : public PixelInterface
{
public:
    Pixel(PIO pio) : PixelInterface(pio){};
    void light_up(const ColorCode &color_code) const
    {
        pio_sm_put_blocking(pio_, 0, color_code.GRB() << 8u);
    }
};