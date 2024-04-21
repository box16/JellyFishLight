#pragma once

#include "Pixel/pixel.h"
#include "RGB/rgb.h"

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

class SimplePattern : public LightPatternInterface {
public:
    void light_up(PixelInterface& pixel_interface, uint pixel_num, uint time) const {
        uint x = time %3;
        for (uint i = 0; i < pixel_num; i++){
            if (x==0)
                pixel_interface.light_up(RGB(0xff, 0, 0));
            else if (x==1)
                pixel_interface.light_up(RGB(0, 0xff, 0));
            else if (x==2)
                pixel_interface.light_up(RGB(0, 0, 0xff));
            else
                pixel_interface.light_up(RGB(0,0,0));       
        }
    }
};