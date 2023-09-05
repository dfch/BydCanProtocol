// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Contract.h>
#include <Word.h>
#include <TemperatureCelsius.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;
    using namespace Temperature;

    #pragma pack(push, 1)
    /// @brief Represents a temperature of the BMS (-40°C to 100°C).
    /// The temperature is represented via a mapping scheme that spans from -40°C to 100°C. 
    /// The range is represented by integers from 0 to 140. 
    /// Values above 100 represent negative temperatures; values below 100 represent positive temperaures. 
    /// For example, a value of 101 corresponds to -1°C.
    struct tagTemperatureBase
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded temperature.
        Word Value;

        /// @brief Returns the temperature in degrees Celsius.
        /// @return The temperature in degrees Celsius.
        TemperatureCelsius ToCelsius() const 
        {
            auto value = Value.ToLittleEndian();
            Contract::Expects([value]
            {
                return value >= 0 && value <= 140;
            }, NAMEOF(ToCelsius));

            const auto offset = 100;

            TemperatureCelsius result(value > 100 ? -1 * (value - offset) : value);

            return result;
        }

        /// @brief Sets the temperature from value in degrees Celsius.
        /// @param value The temperature to set.
        void FromCelsius(TemperatureCelsius value)
        {
            auto v = value.GetValue();
            Contract::Expects([v] { return v > -40 && v <= 100; }, NAMEOF(FromCelsius));

            Value.Value = v;
        }
    };
    #pragma pack(pop)

    /// @brief Represents a temperature of the BMS (-40°C to 100°C).
    /// The temperature is represented via a mapping scheme that spans from -40°C to 100°C. 
    /// The range is represented by integers from 0 to 140. 
    /// Values above 100 represent negative temperatures; values below 100 represent positive temperaures. 
    /// For example, a value of 101 corresponds to -1°C.
    using TemperatureBase = tagTemperatureBase;
}
