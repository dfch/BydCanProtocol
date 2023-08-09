/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include "TemperatureUnit.h"
#include "TemperatureCelsius.h"

namespace Temperature
{
    /// @brief Represents a temperature.
    class Temperature
    {
        private:
            /// @brief The value of the temperature.
            TemperatureCelsius value;

        public:
            /// @brief Default .ctor.
            Temperature();
            /// @brief Creates a temperature with the specified value.
            /// @param value The value of the temperature.
            /// @param unit The unit of the value.
            Temperature(float value, TemperatureUnit unit);

            /// @brief Gets the value of the temperature.
            /// @return A float representing the value of the temperature.
            float GetValue();

            /// @brief Gets the value of the temperature.
            /// @param unit The unit of the value.
            /// @return A float representing the value of the temperature.
            float GetValue(TemperatureUnit unit);

            /// @brief Sets the value of the temperature.
            /// @param value The value of the temperature.
            /// @return A reference to this instance.
            Temperature& SetValue(float value);

            /// @brief Sets the value of the temperature.
            /// @param value The value of the temperature.
            /// @param unit The unit of the value.
            /// @return A reference to this instance.
            Temperature& SetValue(float value, TemperatureUnit unit);

    };
}
