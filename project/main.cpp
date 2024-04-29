/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "ProgrammableLED/WS2812B/WS2812B.h"
#include "ProgrammableLED/LightingPattern/LightingPattern.h"
#include "Switch/TVDT18/TVDT18.h"
#include <memory>
#include <array>
#include <vector>

static constexpr uint8_t PIXEL_NUM = 5;
static constexpr uint8_t LIGHTING_PATTERN_NUM = 3;
static constexpr uint8_t WS2812_PIN = 28;
static constexpr uint8_t SWITCH_PIN = 27;

int main()
{
    stdio_init_all();

    std::array<std::unique_ptr<LightingPatternIF>, LIGHTING_PATTERN_NUM> patterns = {
        std::make_unique<SimplePattern>(RGB(0x7f, 0xff, 0xd4)), // AquaMarine
        std::make_unique<FadePattern>(),
        std::make_unique<RandomFadePattern>()};

    std::unique_ptr<ProgrammableLEDIF> ws2812b = std::make_unique<WS2812B>(pio0,
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
            patterns[switch_counter % LIGHTING_PATTERN_NUM]->Initialize();
            switch_counter++;
        }

        std::vector<RGB> next_rgb = patterns[switch_counter % LIGHTING_PATTERN_NUM]->Next(PIXEL_NUM);
        for (auto rgb : next_rgb)
        {
            ws2812b->LightUp(rgb);
        }

        sleep_ms(50);
    }
}
