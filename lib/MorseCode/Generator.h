// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>

#include "Signal.h"
#include "Configuration.h"

using MorseCode::Configuration;
using MorseCode::Signal;

namespace MorseCode
{
    /// @brief Represents the Morse code generator.
    class Generator
    {
        private:
            /// @brief Represents the ratio between a Dit and a Dah.
            const unsigned short DahDitRatio = 3;

            /// @brief Represents the spacing between Dits/Dahs.
            const unsigned short DitSpacing = 1;

            /// @brief A character spacing is 3 units, but as we already inserted a single unit after the 
            // last character, we only need 2 more units.
            const unsigned short CharacterSpacing = 3 - DitSpacing;

            /// @brief  A word spacing is 7 units, but as we already inserted a character spacing with 
            // 3 units after the last character, we only need 4 more units.
            const unsigned short WordSpacing = 7 - CharacterSpacing - DitSpacing;

            /// @brief Represents a ' ' (space) character.
            const char SPACE = ' ';

            /// @brief Contains the mapping between a character and its Morse code representation.
            const std::map<char, std::vector<Signal>> map = 
            {
                { 'a', { Dit, Dah } },
                { 'b', { Dah, Dit, Dit, Dit } },
                { 'c', { Dah, Dit, Dah, Dit } },
                { 'd', { Dah, Dit, Dit } },
                { 'e', { Dit } },
                { 'f', { Dit, Dit, Dah, Dit } },
                { 'g', { Dah, Dah, Dit } },
                { 'h', { Dit, Dit, Dit, Dit } },
                { 'i', { Dit, Dit } },
                { 'j', { Dit, Dah, Dah, Dah } },
                { 'k', { Dah, Dit, Dah } },
                { 'l', { Dit, Dah, Dit, Dit } },
                { 'm', { Dah, Dah } },
                { 'n', { Dah, Dit } },
                { 'o', { Dah, Dah, Dah } },
                { 'p', { Dit, Dah, Dah, Dit } },
                { 'q', { Dah, Dah, Dit, Dah } },
                { 'r', { Dit, Dah, Dit } },
                { 's', { Dit, Dit, Dit } },
                { 't', { Dah } },
                { 'u', { Dit, Dit, Dah } },
                { 'v', { Dit, Dit, Dit, Dah } },
                { 'w', { Dit, Dah, Dah } },
                { 'x', { Dah, Dit, Dit, Dah } },
                { 'y', { Dah, Dit, Dah, Dah } },
                { 'z', { Dah, Dah, Dit, Dit } },

                { '1', { Dit, Dah, Dah, Dah, Dah } },
                { '2', { Dit, Dit, Dah, Dah, Dah } },
                { '3', { Dit, Dit, Dit, Dah, Dah } },
                { '4', { Dit, Dit, Dit, Dit, Dah } },
                { '5', { Dit, Dit, Dit, Dit, Dit } },
                { '6', { Dah, Dit, Dit, Dit, Dit } },
                { '7', { Dah, Dah, Dit, Dit, Dit } },
                { '8', { Dah, Dah, Dah, Dit, Dit } },
                { '9', { Dah, Dah, Dah, Dah, Dit } },
                { '0', { Dah, Dah, Dah, Dah, Dah } },

                { SPACE, { Word } },
            };

            /// @brief Represents the configuration.
            const std::shared_ptr<Configuration> configuration;
            
        public:
            /// @brief Creates a new instance of the Generator class.
            /// @param cfg The configuration.
            Generator(const std::shared_ptr<Configuration>& cfg);

            /// @brief Serialises the given string into a vector of signals.
            std::vector<Signal> Serialise(std::string& value);

            /// @brief Sends the given string.
            void Send(std::string& value);
            
    };
}
