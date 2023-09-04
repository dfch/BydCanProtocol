// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "TemperatureKelvin.h"

namespace Temperature
{
    /// @brief Represents a temperature in Fahrenheit.
    class TemperatureFahrenheit : public TemperatureKelvin
    {
        private:
            /// @brief The difference between Kelvin and Celsius.
            const float KelvinOffset = 273.15;

            /// @brief The absolute offset from Fahrenheit to Celsius.
            const float CelsiusOffset = 32;
            
            /// @brief The ratio between Fahrenheit and Celsius when converting to Celsius.
            const float FahrenheitCelsiusRatio = 9/5;

            /// @brief The ratio between Celsius and Fahrenheit when converting to Fahrenheit.
            const float CelsiusFahrenheitRatio = 5/9;

            /// @brief Converts the specified value to Kelvin.
            /// @param value The value to convert.
            /// @return The value in Kelvin.
            virtual float ToKelvin(float value);

            /// @brief Converts the specified value from Kelvin to the current unit.
            /// @param value The value to convert.
            /// @return The value in the current unit.
            virtual float FromKelvin(float value);

        public:
            /// @brief Creates a new instance of the TemperatureFahrenheit class with a value of 0.
            TemperatureFahrenheit();

            /// @brief Creates a new instance of the TemperatureFahrenheit class with the specified value.
            /// @param value The value of the temperature.
            TemperatureFahrenheit(float value);

            /// @brief Gets the value of the temperature.
            /// @return A float representing the value of the temperature.
            virtual float GetValue();

            /// @brief Sets the value of the temperature.
            /// @param value The value of the temperature.
            /// @return A reference to this instance.
            virtual TemperatureFahrenheit& SetValue(float value);

    };
}
