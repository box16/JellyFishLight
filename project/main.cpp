/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "ws2812.pio.h"
#include "hardware/pio.h"
#include "Pixel/pixel.h"
#include "LightingPattern/lighting_pattern.h"

static constexpr bool IS_RGBW = false;
static constexpr uint8_t NUM_PIXELS = 5;
static constexpr uint8_t WS2812_PIN = 28;

int main()
{
    stdio_init_all();

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    RandomFadePattern pattern;
    Pixel pixel(pio);
    uint counter = 0;
    while (1)
    {
        pattern.light_up(pixel, NUM_PIXELS, counter);
        counter++;
        sleep_ms(10);
    }
}
