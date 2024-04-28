#pragma once
#include "LightingPatternInterface.h"
#include <algorithm>
#include <random>
#include <cmath>

class SimplePattern : public LightingPatternInterface
{
public:
    SimplePattern(const RGB &rgb) : rgb_(rgb){};
    std::vector<RGB> Next(const uint led_num)
    {
        std::vector<RGB> result(led_num, rgb_);
        return result;
    }
    void Initialize() {};

private:
    RGB rgb_;
};

class RandomFadePattern : public LightingPatternInterface
{
public:
    std::vector<RGB> Next(const uint led_num)
    {
        const float radian = (time % 360) * (M_PI / 180.0);
        const uint8_t color1 = static_cast<uint8_t>((sin(radian) * 0.5 + 0.5) * 255);
        const uint8_t color2 = static_cast<uint8_t>((sin(radian + 2 * M_PI / 3) * 0.5 + 0.5) * 255);
        const uint8_t color3 = static_cast<uint8_t>((sin(radian + 4 * M_PI / 3) * 0.5 + 0.5) * 255);

        std::mt19937 engine(2525);

        std::vector<RGB> result(led_num);
        for (uint i = 0; i < led_num; i++)
        {
            uint8_t colors[3] = {color1, color2, color3};
            std::shuffle(std::begin(colors), std::end(colors), engine);
            result[i] = RGB(colors[0], colors[1], colors[2]);
        }
        time++;
        return result;
    }

    void Initialize()
    {
        time = 0;
    }

private:
    uint64_t time = 0;
};

class FadePattern : public LightingPatternInterface
{
public:
    FadePattern() : LightingPatternInterface(){};
    std::vector<RGB> Next(const uint led_num)
    {
        const float radian = (time % 360) * (M_PI / 180.0);
        const uint8_t red = static_cast<uint8_t>((sin(radian) * 0.5 + 0.5) * 255);
        const uint8_t green = static_cast<uint8_t>((sin(radian + 2 * M_PI / 2) * 0.5 + 0.5) * 255);
        const uint8_t blue = static_cast<uint8_t>((sin(radian + 3 * M_PI / 2) * 0.5 + 0.5) * 255);

        std::vector<RGB> result(led_num);
        for (uint i = 0; i < led_num; i++)
        {
            result[i] = RGB(red, green, blue);
        }
        time++;
        return result;
    }

    void Initialize()
    {
        time = 0;
    }

private:
    uint64_t time = 0;
};