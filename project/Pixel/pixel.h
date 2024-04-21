#pragma once

#include "hardware/pio.h"
#include "RGB/rgb.h"

class PixelInterface{
public:
    PixelInterface(PIO pio) : pio_(pio) {};
    virtual void light_up(RGB rgb) const = 0;
protected:
    PIO pio_;
};

class Pixel : public PixelInterface {
public:
    Pixel(PIO pio) : PixelInterface(pio){};
    void light_up(RGB rgb) const override {
        pio_sm_put_blocking(pio_, 0, rgb.GRB() << 8u);
    }
};