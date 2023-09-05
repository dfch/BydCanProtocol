// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Word.h>
#include <Ampere.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;
    using namespace Units;

    #pragma pack(push, 1)
    /// @brief Represents the current of the BMS.
    /// The curent is represented as centi Ampere.
    /// Negative values indicate BMS is discharging. Positive values indicates BMS is charging.
    struct tagCurrentData
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded Ampere.
        Word Value;

        /// @brief Converts the underlying value to Ampere. 
        /// @return The converted Ampere.
        Ampere ToAmpere() const 
        {
            float offset = 10'000;
            auto value = Value.ToLittleEndian();

            // MSB 1: charging
            // MSB 0: discharging
            
            Ampere result(offset - static_cast<int16_t>(value), Scale::Centi);

            return result;
        }

        /// @brief Sets a voltage to a value.
        /// @param value The value to set.
        void FromAmpere(Ampere value)
        {
            const auto offset = 10'000;

            Value.Value = (offset - value.Value.ScaleTo(Scale::Centi));
        }
    };
    #pragma pack(pop)

    /// @brief Represents a voltage of the BMS.
    /// The voltage is represented as milli volts.
    using CurrentData = tagCurrentData;

    
}
