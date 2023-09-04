// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <stdexcept>

#include "Temperature.h"
#include "TemperatureKelvin.h"
#include "TemperatureCelsius.h"
#include "TemperatureFahrenheit.h"

namespace Temperature
{
    #define NAMEOF(name) #name

    Temperature::Temperature()
        : value()
    {
        // N/A
    }

    float Temperature::GetValue()
    {
        return value.GetValue();
    }

    float Temperature::GetValue(TemperatureUnit unit)
    {
        switch (unit)
        {
            case TemperatureUnit::Kelvin:
                return value.GetValue();
            
            case TemperatureUnit::Celsius:
            {
                TemperatureCelsius t;
                static_cast<TemperatureKelvin>(t).SetValue(value.GetValue());
                // t.Value = value.GetValue();
                return t.GetValue();
            }

            case TemperatureUnit::Fahrenheit:
            {
                TemperatureFahrenheit t;
                static_cast<TemperatureKelvin>(t).SetValue(value.GetValue());
                // t.Value = value.GetValue();
                return t.GetValue();
            }

            default:
                throw std::invalid_argument(NAMEOF(unit));
        }
    }
    
    Temperature &Temperature::SetValue(float value)
    {
        this->value.SetValue(value);

        return *this;
    }
    
    Temperature &Temperature::SetValue(float value, TemperatureUnit unit)
    {
        switch (unit)
        {
            case TemperatureUnit::Kelvin:
            {
                this->value.SetValue(value);
                return *this;
            }
            
            case TemperatureUnit::Celsius:
            {
                TemperatureCelsius t(value);
                this->value.SetValue(static_cast<TemperatureKelvin>(t).GetValue());
                return *this;
            }

            case TemperatureUnit::Fahrenheit:
            {
                TemperatureFahrenheit t(value);
                this->value.SetValue(static_cast<TemperatureKelvin>(t).GetValue());
                return *this;
            }

            default:
                throw std::invalid_argument(NAMEOF(unit));
        }
    }        
}
