/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#pragma once

#include <memory>

#include "driver/gpio.h"
#include "driver/twai.h"

namespace CanTwai
{
    /// @brief Represents the configuration for the CAN bus.
    struct Configuration
    {
        public:
            /// @brief The default GPIO pin to use for transmitting.
            const gpio_num_t GPIO_TX_DEFAULT = GPIO_NUM_21;
            /// @brief The default GPIO pin to use for receiving.
            const gpio_num_t GPIO_RX_DEFAULT = GPIO_NUM_22;

            /// @brief The general configuration for the CAN bus.
            twai_general_config_t General;
            /// @brief The timing configuration for the CAN bus.
            twai_timing_config_t Timing;
            /// @brief The filter configuration for the CAN bus.
            twai_filter_config_t Filter;

            /// @brief Default .ctor.
            Configuration();
            /// @brief .ctor for instantiating a custom configuration.
            /// @param transmit GPIO pin to use for transmitting.
            /// @param receive GPIO pin to use for receiving.
            /// @param mode TWAI mode to use.
            /// @param kbps Speed in kbps to use.
            Configuration(gpio_num_t transmit, gpio_num_t receive, twai_mode_t mode, uint16_t kbps);
    };
}

#endif
