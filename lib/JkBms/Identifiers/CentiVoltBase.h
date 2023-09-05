// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Contract.h>
#include <Word.h>
#include <Volt.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;
    using namespace Units;

    #pragma pack(push, 1)
    /// @brief Represents a voltage of the BMS.
    /// The voltage is represented as centi volts.
    struct tagCentiVoltBase
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded voltage.
        Word Value;

        /// @brief Converts the underlying value to Volt.
        /// @return The converted Volt.
        Volt ToVolt() const 
        {
            auto value = Value.ToLittleEndian();
            Contract::Expects([value] { return value >= 0; }, NAMEOF(ToVolt));

            Volt result(value, Scale::Centi);

            return result;
        }

        /// @brief Sets a voltage to a value.
        /// @param value The value to set.
        void FromVolt(Volt value)
        {
            Contract::Expects([value] { return value.Value.GetValue() >= 0; }, NAMEOF(FromVolt));

            Value.Value = (Word) value.Value.ScaleTo(Scale::Centi);
        }
    };
    #pragma pack(pop)

    using CentiVoltBase = tagCentiVoltBase;    /// @brief Represents a voltage of the BMS.
    /// The voltage is represented as centi volts.

    struct tagBatteryVoltage
    {
        // Intentionally left blank.
    }

    using BatteryVoltage = tagBatteryVoltage;
}
