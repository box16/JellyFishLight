#pragma once

#include "LightingSystem/LightingSystem.h"
#include <cmath>

class SnakePattern : public LightPatternInterface
{
public:
    void light_up(const PixelInterface &pixel_interface,
                  const uint pixel_num,
                  const uint time) const
    {
        for (uint i = 0; i < pixel_num; ++i)
        {
            uint x = (i + (time >> 1)) % 64;
            if (x < 10)
                pixel_interface.light_up(ColorCode(255, 0, 0));
            else if (x >= 15 && x < 25)
                pixel_interface.light_up(ColorCode(0, 255, 0));
            else if (x >= 30 && x < 40)
                pixel_interface.light_up(ColorCode(0, 0, 255));
            else
                pixel_interface.light_up(ColorCode(0, 0, 0));
        }
    }
};

class FadePattern : public LightPatternInterface
{
public:
    void light_up(const PixelInterface &pixel_interface,
                  const uint pixel_num,
                  const uint time) const
    {
        const float radian = (time % 360) * (M_PI / 180.0);
        const uint8_t red = static_cast<uint8_t>((sin(radian) * 0.5 + 0.5) * 255);
        const uint8_t green = static_cast<uint8_t>((sin(radian + 2 * M_PI / 2) * 0.5 + 0.5) * 255);
        const uint8_t blue = static_cast<uint8_t>((sin(radian + 3 * M_PI / 2) * 0.5 + 0.5) * 255);

        for (uint i = 0; i < pixel_num; i++)
        {
            pixel_interface.light_up(ColorCode(red, green, blue));
        }
    }
};