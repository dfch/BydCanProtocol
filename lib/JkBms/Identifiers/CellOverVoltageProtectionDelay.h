// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Contract.h>
#include <Word.h>
#include <Second.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;
    using namespace Units;

    #pragma pack(push, 1)
    /// @brief Represents the Cell Over Voltage Protection Delay in seconds of the BMS (1..60).
    struct tagCellOverVoltageProtectionDelay
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded seconds.
        Word Value;

        /// @brief Converts the underlying value to seconds. 
        /// @return The converted second.
        Second ToSecond() const 
        {
            auto value = Value.ToLittleEndian();
            Contract::Expects([s] { return 1 <= value && 60 >= value; });

            Second result(value);

            return result;
        }

        /// @brief Sets the underlying value.
        /// @param value The value in seconds to set.
        void FromSecond(Second value)
        {
            auto s = value.Value.GetValue();
            Contract::Expects([s] { return 1 <= s && 60 >= s; });

            Value.Value = value.Value.GetValue();
        }
    };
    #pragma pack(pop)

    /// @brief Represents the Cell Over Voltage Protection Delay in seconds of the BMS (1..60).
    using CellOverVoltageProtectionDelay = tagCellOverVoltageProtectionDelay;
}
