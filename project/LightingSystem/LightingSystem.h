#pragma once

#include "hardware/pio.h"

class ColorCode
{
public:
    ColorCode(const uint8_t red,
              const uint8_t green,
              const uint8_t blue)
        : red_(red), green_(green), blue_(blue)
    {
    }

    uint32_t GRB() const
    {
        return (static_cast<uint32_t>(green_) << 16) |
               (static_cast<uint32_t>(red_) << 8) |
               (static_cast<uint32_t>(blue_));
    }

private:
    uint8_t red_;
    uint8_t green_;
    uint8_t blue_;
};

class PixelInterface
{
public:
    PixelInterface(const PIO &pio) : pio_(pio){};
    virtual void light_up(const ColorCode &color_code) const = 0;

protected:
    PIO pio_;
};

class LightPatternInterface
{
public:
    virtual void light_up(const PixelInterface &pixel_interface,
                          const uint len,
                          const uint time) const = 0;
};
