/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

#include <Scale.h>

namespace Units
{
    /// @brief The base value of a unit.
    class Value
    {
        private:
            /// @brief Represents the scaling factors.
            const float nano = float(1'000'000'000);
            const float micro = float(1'000'000);
            const float milli = float(1'000);
            const float centi = float(100);
            const float percent = float(100);
            const float deci = float(10);
            const float deka = float(10);
            const float hecto = float(100);
            const float kilo = float(1'000);
            const float myria = float(10'000);
            const float mega = float(1'000'000);
            const float giga = float(1'000'000'000);
            const float tera = float(1'000'000'000'000);

            /// @brief Represents the value of the unit.
            float value;

            /// @brief Scales the specified value to a given factor as specifed by tag.
            /// @param value The value to scale.
            /// @param tag The tag representing the factor to scale.
            /// @return The scaled value.
            float ScaleTo(float value, Scale tag) const;

            /// @brief Scales the specified value from a given factor as specifed by tag.
            /// @param value The value to scale.
            /// @param tag The tag representing the factor to scale.
            /// @return The scaled value.
            float ScaleFrom(float value, Scale tag) const;

        public:
            /// @brief Default .ctor.
            Value();
            
            /// @brief Creates an instance of Value with the specified value.
            /// @param value The value.
            Value(float value);
            
            /// @brief Creates an instance of Value with the specified value and scales it from the given magnitude as specified by tag.
            /// @param value The value.
            /// @param tag The tag representing the factor to scale.
            Value(float value, Scale tag);

            /// @brief Gets the current value of Value.
            /// @return A float representing the value of Value.
            float GetValue() const;

            /// @brief Sets the value of Value.
            /// @param value The new value.
            /// @return A reference to this instance.
            Value& SetValue(float value);

            /// @brief Scales Value to a given factor as specifed by tag.
            /// @param tag The tag representing the magnitude to scale.
            /// @return The scaled value.
            float ScaleTo(Scale tag) const;

            /// @brief Scales Value to a given factor as specifed by tag.
            /// @param tag The tag representing the factor to scale.
            /// @param round True, if the returned value is mathematically rounded; false, otherwise.
            /// @return The scaled value.
            float ScaleTo(Scale tag, bool round) const;

    };
}
