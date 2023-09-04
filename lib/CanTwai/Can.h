// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#if defined(ESP_PLATFORM)

#pragma once

#include <memory>

#include "driver/gpio.h"
#include "driver/twai.h"

#include "Configuration.h"
#include <Message.h>

namespace CanTwai
{
    /// @brief Represents the CAN bus.
    class Can
    {
        private:
            /// @brief A CAN bus message.
            twai_message_t message;

            /// @brief Creates a CAN bus message.
            /// @param data The data to create the message from.
            /// @return A CAN bus message.
            twai_message_t CreateMessage(std::shared_ptr<Byd::Message> data);

        public:
            /// @brief Default .ctor.
            Can(twai_general_config_t* general, twai_timing_config_t* timing, twai_filter_config_t* filter);
            
            /// @brief Emulates the BYD LVS CAN bus protocol when communicating with Venus OS.
            /// @return True when the messages could sent successfully. False, otherwise.
            bool EmulateByd();

            /// @brief Emulates the BYD LVS CAN bus protocol when communicating with Venus OS by composing all messages in binary form.
            /// @return True when the messages could sent successfully. False, otherwise.
            bool EmulateBydBinary();

        /// @brief Factory class for the Can class.
        class Factory
        {
            private:
                /// @brief Default .ctor. Not supported.
                Factory() = delete;

            public:
                /// @brief Creates an instance of the Can class.
                /// @param cfg Configuration for the CAN bus.
                /// @param timing Timing configuration for the CAN bus.
                /// @param filter Filter configuration for the CAN bus.
                /// @return An instance to the Can class.
                static std::shared_ptr<Can> Create(twai_general_config_t* cfg, twai_timing_config_t* timing, twai_filter_config_t* filter);
                
                /// @brief Creates an instance of the Can class.
                /// @param configuration Configuration for the CAN bus.
                /// @return An instance to the Can class.
                static std::shared_ptr<Can> Create(std::shared_ptr<Configuration> configuration);
        };
    };
}

#endif
