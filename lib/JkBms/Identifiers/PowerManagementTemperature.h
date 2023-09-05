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
    /// @brief Represents the temperature of the BMS (-40°C to 100°C).
    /// The temperature is represented via a mapping scheme that spans from -40°C to 100°C. 
    /// The range is represented by integers from 0 to 140. 
    /// Values above 100 represent negative temperatures; values below 100 represent positive temperaures. 
    /// For example, a value of 101 corresponds to -1°C.
    struct tagPowerManagementTemperature
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded temperature.
        Word Value;

        /// @brief Returns the temperature in degrees Celsius.
        /// @return The temperature in degrees Celsius.
        TemperatureCelsius ToCelsius() const 
        {
            Contract::Expects([this]
            {
                auto v = this->Value.ToLittleEndian();

                return v >= 0 && v <= 140;
            }, NAMEOF(Temperature::TemperatureCelsius));

            const auto offset = 100;
            auto value = Value.ToLittleEndian();

            TemperatureCelsius result(value > 100 ? -1 * (value - offset) : value);

            return result;
        }
    };
    #pragma pack(pop)

    using PowerManagementTemperature = tagPowerManagementTemperature;
}
