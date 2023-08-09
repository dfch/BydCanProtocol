/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#include "Pin.h"

using Gpio::Pin;

namespace Gpio
{
    Pin::Pin(const gpio_num_t number, gpio_mode_t mode)
        : number(number), mode(mode)
    {
        gpio_reset_pin(number);
        gpio_set_direction(number, GPIO_MODE_OUTPUT);
    }

    bool Pin::Get()
    {
        auto level = gpio_get_level(number);
        auto result = level == High ? true : false;
        
        return result;
    }

    void Pin::Set(bool flag)
    {
        gpio_set_level(number, flag ? High : Low);
    }
}

#endif
