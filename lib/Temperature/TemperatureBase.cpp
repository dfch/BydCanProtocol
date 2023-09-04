// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include "TemperatureBase.h"

namespace Temperature
{
    TemperatureBase::TemperatureBase(float value)
        : Value(value)
    {
        // N/A
    }

    float TemperatureBase::GetValue()
    {
        return Value;
    }

    TemperatureBase& TemperatureBase::SetValue(float value)
    {
        Value = value;

        return *this;
    }
}
