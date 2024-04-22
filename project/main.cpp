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
#include <memory>
#include <array>

static constexpr bool IS_RGBW = false;
static constexpr uint8_t NUM_PIXELS = 5;
static constexpr uint8_t WS2812_PIN = 28;
static constexpr uint8_t SWITCH = 27;
static constexpr uint8_t PATTERN_NUM = 3;

int main()
{
    stdio_init_all();
    gpio_init(SWITCH);
    gpio_set_dir(SWITCH, GPIO_IN);
    gpio_pull_down(SWITCH);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);

    std::array<std::unique_ptr<LightPatternInterface>, PATTERN_NUM> patterns = {
        std::make_unique<SimpleAquaMarinePattern>(),
        std::make_unique<FadePattern>(),
        std::make_unique<RandomFadePattern>()};
    Pixel pixel(pio);
    uint counter = 0;

    uint switch_counter = 0;
    uint64_t last_debounce_time = 0;
    const uint64_t debounce_delay = 200;

    while (1)
    {
        bool button_pressed = gpio_get(SWITCH) == 1;
        if (button_pressed)
        {
            uint64_t current_time = to_us_since_boot(get_absolute_time());
            if (current_time - last_debounce_time > debounce_delay * 1000)
            {
                switch_counter++;
                last_debounce_time = current_time;
                counter = 0;
            }
        }
        patterns[switch_counter % PATTERN_NUM]->light_up(pixel, NUM_PIXELS, counter);
        counter++;
        sleep_ms(50);
    }
}
