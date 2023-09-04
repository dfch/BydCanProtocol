// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <functional>

namespace MorseCode
{
    /// @brief Represents the configuration of the MorseCode generator.
    class Configuration
    {
        public:
            /// @brief The default length of a dit in milliseconds.
            const unsigned short DitLengthMsDefault = 150;

            /// @brief The length of a dit in milliseconds.
            unsigned short DitLengthMs = DitLengthMsDefault;

            /// @brief The function to call when a signal is transmitted.
            std::function<void(int ms)> Transmit = [](int ms) { return; };
            /// @brief The function to call when no signal is transmitted.
            std::function<void(int ms)> NoTransmit = [](int ms) { return; };

    };
}
