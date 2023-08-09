/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include "TemperatureKelvin.h"

namespace Temperature
{
    /// @brief Represents a temperature in Celsius.
    class TemperatureCelsius : public TemperatureKelvin
    {
        private:
            /// @brief The difference between Kelvin and Celsius.
            const float KelvinOffset = 273.15;

            /// @brief Converts the specified value to Kelvin.
            /// @param value The value to convert.
            /// @return The value in Kelvin.
            virtual float ToKelvin(float value);

            /// @brief Converts the specified value from Kelvin to the current unit.
            /// @param value The value to convert.
            /// @return The value in the current unit.
            virtual float FromKelvin(float value);

        public:
            /// @brief Creates a new instance of the TemperatureCelsius class with a value of 0.
            TemperatureCelsius();

            /// @brief Creates a new instance of the TemperatureCelsius class with the specified value.
            /// @param value The value of the temperature.
            TemperatureCelsius(float value);

            /// @brief Gets the value of the temperature.
            /// @return A float representing the value of the temperature.
            virtual float GetValue();

            /// @brief Sets the value of the temperature.
            /// @param value The value of the temperature.
            /// @return A reference to this instance.
            virtual TemperatureCelsius& SetValue(float value);

    };
}
