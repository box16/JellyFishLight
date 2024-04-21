#pragma once

#include "Pixel/pixel.h"
#include "RGB/rgb.h"
#include <cmath>

class LightPatternInterface{
public:
    virtual void light_up(PixelInterface& pixel_interface, uint len,uint t) const = 0;
};

class SnakePattern : public LightPatternInterface {
public:
    void light_up(PixelInterface& pixel_interface, uint pixel_num, uint time) const {
        for (uint i = 0; i < pixel_num; ++i) {
            uint x = (i + (time >> 1)) % 64;
            if (x < 10)
                pixel_interface.light_up(RGB(0xff, 0, 0));
            else if (x >= 15 && x < 25)
                pixel_interface.light_up(RGB(0, 0xff, 0));
            else if (x >= 30 && x < 40)
                pixel_interface.light_up(RGB(0, 0, 0xff));
            else
                pixel_interface.light_up(RGB(0,0,0));
        }      
    }
};

class FadePattern : public LightPatternInterface {
public:
    void light_up(PixelInterface& pixel_interface, uint pixel_num, uint time) const {
        double phase = (time % 360) * (M_PI / 180.0);  // 時間をラジアンに変換
        uint8_t red_intensity = static_cast<uint8_t>((sin(phase) * 0.5 + 0.5) * 255);
        uint8_t green_intensity = static_cast<uint8_t>((sin(phase + 2 * M_PI / 2) * 0.5 + 0.5) * 255);
        uint8_t blue_intensity = static_cast<uint8_t>((sin(phase + 3 * M_PI / 2) * 0.5 + 0.5) * 255);

        for (uint i = 0; i < pixel_num; i++) {
            pixel_interface.light_up(RGB(red_intensity, green_intensity, blue_intensity));
        }

    }
};