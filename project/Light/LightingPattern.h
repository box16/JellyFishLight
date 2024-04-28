#pragma once
#include "LightingPatternInterface.h"
#include <algorithm>
#include <random>
#include <cmath>

class SimpleAquaMarinePattern : public LightingPatternInterface
{
public:
    std::vector<RGB> LightUp(const LEDInterface &led_interface,
                             const uint pixel_num,
                             const uint time) const
    {
        std::vector<RGB> result(pixel_num);
        for (uint i = 0; i < pixel_num; i++)
        {
            result[i] = RGB(0x7f, 0xff, 0xd4);
            led_interface.LightUp(result[i]);
        }
        return result;
    }
};

class RandomFadePattern : public LightingPatternInterface
{
public:
    std::vector<RGB> LightUp(const LEDInterface &led_interface,
                             const uint pixel_num,
                             const uint time) const
    {
        const float radian = (time % 360) * (M_PI / 180.0);
        const uint8_t color1 = static_cast<uint8_t>((sin(radian) * 0.5 + 0.5) * 255);
        const uint8_t color2 = static_cast<uint8_t>((sin(radian + 2 * M_PI / 3) * 0.5 + 0.5) * 255);
        const uint8_t color3 = static_cast<uint8_t>((sin(radian + 4 * M_PI / 3) * 0.5 + 0.5) * 255);

        std::random_device rd;
        std::mt19937 g(rd());

        std::vector<RGB> result(pixel_num);
        for (uint i = 0; i < pixel_num; i++)
        {
            uint8_t colors[3] = {color1, color2, color3};
            std::shuffle(std::begin(colors), std::end(colors), g);
            result[i] = RGB(colors[0], colors[1], colors[2]);
            led_interface.LightUp(result[i]);
        }
        return result;
    }
};

class FadePattern : public LightingPatternInterface
{
public:
    std::vector<RGB> LightUp(const LEDInterface &led_interface,
                             const uint pixel_num,
                             const uint time) const
    {
        const float radian = (time % 360) * (M_PI / 180.0);
        const uint8_t red = static_cast<uint8_t>((sin(radian) * 0.5 + 0.5) * 255);
        const uint8_t green = static_cast<uint8_t>((sin(radian + 2 * M_PI / 2) * 0.5 + 0.5) * 255);
        const uint8_t blue = static_cast<uint8_t>((sin(radian + 3 * M_PI / 2) * 0.5 + 0.5) * 255);

        std::vector<RGB> result(pixel_num);
        for (uint i = 0; i < pixel_num; i++)
        {
            result[i] = RGB(red, green, blue);
            led_interface.LightUp(result[i]);
        }
        return result;
    }
};