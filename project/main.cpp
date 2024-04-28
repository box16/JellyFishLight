/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "Light/WS2812B.h"
#include "Light/LightingPattern.h"
#include "Switch/TVDT18.h"
#include <memory>
#include <array>
#include <vector>

static constexpr uint8_t NUM_PIXELS = 5;
static constexpr uint8_t WS2812_PIN = 28;
static constexpr uint8_t SWITCH_PIN = 27;
static constexpr uint8_t PATTERN_NUM = 3;

int main()
{
    stdio_init_all();

    std::array<std::unique_ptr<LightingPatternInterface>, PATTERN_NUM> patterns = {
        std::make_unique<SimplePattern>(RGB(0x7f, 0xff, 0xd4)),
        std::make_unique<FadePattern>(),
        std::make_unique<RandomFadePattern>()};

    std::unique_ptr<LEDInterface> ws2812b = std::make_unique<WS2812B>(pio0,
                                                                      0,
                                                                      WS2812_PIN,
                                                                      800000,
                                                                      false);

    uint switch_counter = 0;
    std::unique_ptr<SwitchInterface> tvdt18 = std::make_unique<TVDT18>(SWITCH_PIN,
                                                                       500);

    while (1)
    {
        tvdt18->CheckPress();
        if (tvdt18->IsSwitched())
        {
            switch_counter++;
        }

        std::vector<RGB> next_rgb = patterns[switch_counter % PATTERN_NUM]->Next(NUM_PIXELS);
        for (auto rgb : next_rgb)
        {
            ws2812b->LightUp(rgb);
        }

        sleep_ms(50);
    }
}
