#pragma once
#include "LEDInterface.h"
#include "ws2812.pio.h"

class WS2812B : public LEDInterface
{
public:
    WS2812B(PIO pio,
            int state_machine,
            uint8_t output_pin,
            uint32_t frequency,
            bool is_rgbw_mode) : pio_(pio), state_machine_(state_machine)
    {
        uint offset = pio_add_program(pio_, &ws2812_program);
        ws2812_program_init(pio_, state_machine_, offset, output_pin, frequency, is_rgbw_mode);
    }

    void light_up(const RGB &rgb) const
    {
        pio_sm_put_blocking(pio_,
                            state_machine_,
                            (rgb.GetGreen() << 16 | rgb.GetRed() << 8 | rgb.GetBlue()) << 8u);
    }

private:
    PIO pio_;
    int state_machine_;
};