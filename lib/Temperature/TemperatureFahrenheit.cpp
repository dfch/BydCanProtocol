/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include "TemperatureFahrenheit.h"

namespace Temperature
{
    float TemperatureFahrenheit::ToKelvin(float value)
    {
        return (value - CelsiusOffset) * CelsiusFahrenheitRatio + KelvinOffset;
    }

    float TemperatureFahrenheit::FromKelvin(float value)
    {
        return (value - KelvinOffset) * FahrenheitCelsiusRatio + CelsiusOffset;
    }

    TemperatureFahrenheit::TemperatureFahrenheit()
        : TemperatureFahrenheit(0)
    {
        // N/A
    }

    TemperatureFahrenheit::TemperatureFahrenheit(float value)
    {
        Value = ToKelvin(value);
    }

    float TemperatureFahrenheit::GetValue()
    {
        return FromKelvin(Value);
    }

    TemperatureFahrenheit& TemperatureFahrenheit::SetValue(float value)
    {
        Value = ToKelvin(value);

        return *this;
    }
}
