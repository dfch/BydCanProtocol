// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "TemperatureBase.h"

namespace Temperature
{
    #define NAMEOF(name) #name

    /// @brief Represents a temperature in Celsius.
    class TemperatureKelvin : public TemperatureBase
    {
        private:
            /// @brief Converts the specified value to Kelvin.
            /// @param value The value to convert.
            /// @return The value in Kelvin.
            virtual float ToKelvin(float value);

            /// @brief Converts the specified value from Kelvin to the current unit.
            /// @param value The value to convert.
            /// @return The value in the current unit.
            virtual float FromKelvin(float value);

        public:
            /// @brief Creates a new instance of the TemperatureKelvin class with a value of 0.
            TemperatureKelvin();

            /// @brief Creates a new instance of the TemperatureKelvin class with the specified value.
            /// @param value The value of the temperature.
            TemperatureKelvin(float value);

            /// @brief Gets the value of the temperature.
            /// @return A float representing the value of the temperature.
            virtual float GetValue();

            /// @brief Sets the value of the temperature.
            /// @param value The value of the temperature.
            /// @return A reference to this instance.
            virtual TemperatureKelvin& SetValue(float value);

    };
}
