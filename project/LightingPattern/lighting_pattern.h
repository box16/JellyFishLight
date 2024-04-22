#pragma once

#include "LightingSystem/LightingSystem.h"
#include <algorithm>
#include <random>
#include <cmath>

class RandomFadePattern : public LightPatternInterface
{
public:
    void light_up(const PixelInterface &pixel_interface,
                  const uint pixel_num,
                  const uint time) const
    {
        const float radian = (time % 360) * (M_PI / 180.0);
        const uint8_t color1 = static_cast<uint8_t>((sin(radian) * 0.5 + 0.5) * 255);
        const uint8_t color2 = static_cast<uint8_t>((sin(radian + 2 * M_PI / 3) * 0.5 + 0.5) * 255);
        const uint8_t color3 = static_cast<uint8_t>((sin(radian + 4 * M_PI / 3) * 0.5 + 0.5) * 255);

        std::random_device rd;
        std::mt19937 g(rd());

        for (uint i = 0; i < pixel_num; i++)
        {
            uint8_t colors[3] = {color1, color2, color3};
            std::shuffle(std::begin(colors), std::end(colors), g);
            pixel_interface.light_up(ColorCode(colors[0], colors[1], colors[2]));
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