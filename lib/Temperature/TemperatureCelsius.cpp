/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include "TemperatureCelsius.h"

namespace Temperature
{
    float TemperatureCelsius::ToKelvin(float value)
    {
        return value + KelvinOffset;
    }

    float TemperatureCelsius::FromKelvin(float value)
    {
        return value - KelvinOffset;
    }

    TemperatureCelsius::TemperatureCelsius()
        : TemperatureCelsius(0)
    {
        // N/A
    }

    TemperatureCelsius::TemperatureCelsius(float value)
    {
        Value = ToKelvin(value);
    }

    float TemperatureCelsius::GetValue()
    {
        return FromKelvin(Value);
    }

    TemperatureCelsius& TemperatureCelsius::SetValue(float value)
    {
        Value = ToKelvin(value);

        return *this;
    }
}
