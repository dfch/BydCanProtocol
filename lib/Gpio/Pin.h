/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#pragma once

#include <driver/gpio.h>

namespace Gpio
{
    #define LED GPIO_NUM_13

    /// @brief Represents a GPIO pin.
    class Pin
    {
        private:
            // @brief The low state of a GPIO pin.
            const int Low = 0;
            // @brief The high state of a GPIO pin.
            const int High = 1;
            
            // @brief The number of the GPIO pin.
            const gpio_num_t number;
            // @brief The mode of the GPIO pin.
            const gpio_mode_t mode;

        public:
            // @brief Default .ctor.
            // @param number The number of the GPIO pin.
            // @param mode The mode of the GPIO pin.
            Pin(const gpio_num_t number, gpio_mode_t mode);

            // @brief Gets the state of the GPIO pin.
            bool Get();
            // @brief Sets the state of the GPIO pin.
            // @param flag The state of the GPIO pin. True for high. False for low.
            void Set(bool flag);
            
    };
}

#endif
