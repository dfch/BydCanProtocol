/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#include "Configuration.h"

using CanTwai::Configuration;

namespace CanTwai
{
    Configuration::Configuration()
    {
        General = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_TX_DEFAULT, GPIO_RX_DEFAULT, TWAI_MODE_NORMAL);
        
        Timing = TWAI_TIMING_CONFIG_500KBITS();
        
        Filter = TWAI_FILTER_CONFIG_ACCEPT_ALL();
    }

    Configuration::Configuration(gpio_num_t transmit, gpio_num_t receive, twai_mode_t mode, uint16_t kbps)
    {
        General = TWAI_GENERAL_CONFIG_DEFAULT(transmit, receive, mode);

        switch(kbps)
        {
            case 250:
                Timing = TWAI_TIMING_CONFIG_250KBITS();
                break;
            case 500:
                Timing = TWAI_TIMING_CONFIG_500KBITS();
                break;
            default:
                throw;
        }

        Filter = TWAI_FILTER_CONFIG_ACCEPT_ALL();
    }
}

#endif
