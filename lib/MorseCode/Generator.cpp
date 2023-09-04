// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include "Generator.h"

namespace MorseCode
{
    Generator::Generator(const std::shared_ptr<Configuration>& cfg)
        : configuration(cfg)
    {
        // N/A
    }

    void Generator::Send(std::string& value)
    {
        auto result = Serialise(value);

        for (auto s : result)
        {
            switch (s)
            {
                case Dit:
                    configuration->Transmit(configuration->DitLengthMs);
                    configuration->NoTransmit(DitSpacing * configuration->DitLengthMs);
                    break;
                case Dah:
                    configuration->Transmit(DahDitRatio * configuration->DitLengthMs);
                    configuration->NoTransmit(DitSpacing * configuration->DitLengthMs);
                    break;
                case Char:
                    configuration->NoTransmit(CharacterSpacing * configuration->DitLengthMs);
                    break;
                case Word:
                    configuration->NoTransmit(WordSpacing * configuration->DitLengthMs);
                    break;
                default:
                    throw;
            }
        }
    }

    std::vector<Signal> Generator::Serialise(std::string& value)
    {
        std::vector<Signal> result;

        // Trim leading/trailing ' ' characters.
        std::size_t start = value.find_first_not_of(SPACE);
        std::size_t end = value.find_last_not_of(SPACE);
        auto trimmedValue = start == end ? std::string() : value.substr(start, end - start + 1);

        // Convert to lower case.
        transform(trimmedValue.begin(), trimmedValue.end(), trimmedValue.begin(), 
            [](unsigned char c){ return ::tolower(c); });
        
        // Approximate the final vector size.
        result.reserve(trimmedValue.length() * 2* CharacterSpacing + WordSpacing);
        
        for(const auto c : trimmedValue)
        {
            if(map.find(c) == map.end()) continue;

            auto signal = map.at(c);

            for(const auto s : signal)
            {
                result.push_back(s);
            }

            result.push_back(Char);
        }

        result.push_back(Word);

        return result;
    }
}
