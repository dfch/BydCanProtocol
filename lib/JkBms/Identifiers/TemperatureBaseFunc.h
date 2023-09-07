// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <concepts>

#include <Word.h>
#include <TemperatureCelsius.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;
    using namespace Temperature;

    /// @brief Specifies a callable to be used as a getter.
    template<typename T>
    concept TemperatureGetter = 
        std::invocable<T, Word> && 
        std::same_as<std::invoke_result_t<T, Word>, TemperatureCelsius>;
    
    /// @brief Specifies a callable to be used as a setter.
    template<typename CallableSetter>
    concept TemperatureSetter = 
        std::invocable<CallableSetter, TemperatureCelsius> && 
        std::same_as<std::invoke_result_t<CallableSetter, TemperatureCelsius>, Word>;

    #pragma pack(push, 1)
    /// @brief A template for representing a temperature in degrees Celsius.
    /// @tparam TGet Getter for converting the temperature from the underlying value. 
    /// @tparam TSet Setter for converting the temperature to the underlying value.
    template<TemperatureGetter TGet, TemperatureSetter TSet>
    struct tagTemperatureBaseFunc
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded temperature.
        Word Value;

        /// @brief Returns the temperature of the underyling value.
        /// @return The temperature in degrees Celsius.
        TemperatureCelsius ToCelsius() const 
        {
            return TGet()(Value);
        }

        /// @brief Sets the temperature to the underlying value.
        /// @param value The temperature in degrees Celsius.
        void FromCelsius(TemperatureCelsius value)
        {
            auto result = TSet()(value);
            
            Value.Value = result;
        }
    };
    #pragma pack(pop)
}
