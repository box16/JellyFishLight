#pragma once
#include "Switch/SwitchIF.h"

class TVDT18 : public SwitchIF
{
public:
    TVDT18(const uint8_t switch_pin,
           const uint64_t debounce_thr_ms)
        : SWITCH_PIN(switch_pin),
          DEBOUNCE_THR_MS(debounce_thr_ms)
    {
        gpio_init(SWITCH_PIN);
        gpio_set_dir(SWITCH_PIN, GPIO_IN);
        gpio_pull_down(SWITCH_PIN);
    }

    void CheckPress()
    {
        uint64_t current_time = to_ms_since_boot(get_absolute_time());

        if (gpio_get(SWITCH_PIN) == 1)
        {
            if ((current_time - last_pressed_time) > DEBOUNCE_THR_MS)
            {
                is_switched = true;
                last_pressed_time = current_time;
            }
            else
            {
                is_switched = false;
            }
        }
        else
        {
            last_pressed_time = current_time;
            is_switched = false;
        }
    }

    bool IsSwitched() const
    {
        return is_switched;
    }

private:
    uint64_t last_pressed_time = 0;
    bool is_switched = false;

private:
    uint8_t SWITCH_PIN;
    uint64_t DEBOUNCE_THR_MS;
};
