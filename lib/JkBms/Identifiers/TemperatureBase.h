// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts>
#include <cstddef>

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
    /// @brief A template for representing a temperature in degrees Celsius.
    /// @tparam TGet Getter for converting the temperature from the underlying value. 
    /// @tparam TSet Setter for converting the temperature to the underlying value.
    template<size_t TMin, size_t TMax>
    struct tagTemperatureBase
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded temperature.
        Word Value;

        /// @brief Returns the temperature of the underyling value.
        /// @return The temperature in degrees Celsius.
        TemperatureCelsius ToCelsius() const 
        {
            auto value = Value.ToLittleEndian();
            Contract::Expects([value] { return TMin >= value && TMax <= value; }, "tagTemperatureBase::ToCelsius");

            auto result = TemperatureCelsius(value);

            return result;
        }

        /// @brief Sets the temperature to the underlying value.
        /// @param value The temperature in degrees Celsius.
        void FromCelsius(TemperatureCelsius value)
        {
            auto t = value.GetValue();
            Contract::Expects([value] { return TMin >= t && TMax <= t; }, "tagTemperatureBase::FromCelsius");

            Value.Value = t;
        }
    };
    #pragma pack(pop)
}
