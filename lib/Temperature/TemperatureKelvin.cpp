// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <Contract.h>

#include "TemperatureKelvin.h"

namespace Temperature
{
    float TemperatureKelvin::ToKelvin(float value)
    {
        return value;
    }

    float TemperatureKelvin::FromKelvin(float value)
    {
        return value;
    }

    TemperatureKelvin::TemperatureKelvin()
        : TemperatureKelvin(0)
    {
        // N/A
    }

    TemperatureKelvin::TemperatureKelvin(float value)
        : TemperatureBase(value)
    {
        Contract::Expects([value] { return value >= 0; });
    }

    float TemperatureKelvin::GetValue()
    {
        return FromKelvin(Value);
    }

    TemperatureKelvin& TemperatureKelvin::SetValue(float value)
    {
        Contract::Expects([value] { return value >= 0; });

        Value = ToKelvin(value);

        return *this;
    }
}
