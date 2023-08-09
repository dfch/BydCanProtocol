/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

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
