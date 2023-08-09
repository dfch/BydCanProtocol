/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

namespace Temperature
{
    #define NAMEOF(name) #name

    /// @brief Abstract base class for representing a temperature.
    class TemperatureBase
    {
        private:
            /// @brief Converts the specified value to Kelvin. Pure virtual. 
            /// @param value The value to convert.
            /// @return The value in Kelvin.
            virtual float ToKelvin(float value) = 0;

            /// @brief Converts the specified value from Kelvin to the current unit. Pure virtual.
            /// @param value The value to convert.
            /// @return The value in the current unit.
            virtual float FromKelvin(float value) = 0;

        protected:
            /// @brief Creates a new instance of the TemperatureBase class with the specified value.
            /// @param value The value of the temperature.
            TemperatureBase(float value);

            /// @brief The value of the temperature.
            float Value;

        public:
            /// @brief Gets the value of the temperature.
            /// @return A float representing the value of the temperature.
            virtual float GetValue();

            /// @brief Sets the value of the temperature.
            /// @param value The value of the temperature.
            /// @return A reference to this instance.
            virtual TemperatureBase& SetValue(float value);

    };

}
