// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <cstdint>
#include <stdexcept>
#include <tgmath.h>

#include <Contract.h>

#include "Value.h"

namespace Units
{
    float Value::ScaleTo(float value, Scale tag) const
    {
        float result;

        switch (tag)
        {
            case Units::Scale::Nano:
                result = value * nano;
                break;
            
            case Units::Scale::Micro:
                result = value * micro;
                break;
            
            case Units::Scale::Milli:
                result = value * milli;
                break;
            
            case Units::Scale::Centi:
            case Units::Scale::Percent:
                result = value * centi;
                break;
            
            case Units::Scale::Deci:
                result = value * deci;
                break;
            
            case Units::Scale::Default:
                result = value;
                break;
            
            case Units::Scale::Deka:
                result = value / deka;
                break;
            
            case Units::Scale::Hecto:
                result = value / hecto;
                break;
            
            case Units::Scale::Kilo:
                result = value / kilo;
                break;
            
            case Units::Scale::Myria:
                result = value / myria;
                break;
            
            case Units::Scale::Mega:
                result = value / mega;
                break;
            
            default:
                throw std::invalid_argument(NAMEOF(tag));
        }

        return result;
    }

    float Value::ScaleFrom(float value, Scale tag) const
    {
        float result;

        switch (tag)
        {
            case Units::Scale::Nano:
                result = value / nano;
                break;
            
            case Units::Scale::Micro:
                result = value / micro;
                break;
            
            case Units::Scale::Milli:
                result = value / milli;
                break;
            
            case Units::Scale::Centi:
            case Units::Scale::Percent:
                result = value / centi;
                break;
            
            case Units::Scale::Deci:
                result = value / deci;
                break;
            
            case Units::Scale::Default:
                result = value;
                break;
            
            case Units::Scale::Deka:
                result = value * deka;
                break;
            
            case Units::Scale::Hecto:
                result = value * hecto;
                break;
            
            case Units::Scale::Kilo:
                result = value * kilo;
                break;
            
            case Units::Scale::Myria:
                result = value * myria;
                break;
            
            case Units::Scale::Mega:
                result = value * mega;
                break;
            
            case Units::Scale::Giga:
                result = value * giga;
                break;
            
            case Units::Scale::Tera:
                result = value * tera;
                break;
            
            default:
                throw std::invalid_argument(NAMEOF(tag));
        }

        return result;
    }

    Value::Value()
        : value(0)
    {
        // N/A
    }

    Value::Value(float value)
        : value(value)
    {
        // N/A
    }

    Value::Value(float value, Scale tag)
        : value(ScaleFrom(value, tag))
    {
        // N/A
    }
    

    float Value::GetValue() const
    {
        return value;
    }

    Value& Value::SetValue(float value)
    {
        this->value = value;

        return *this;
    }

    float Value::ScaleTo(Scale tag) const
    {
        return ScaleTo(tag, false);
    }

    float Value::ScaleTo(Scale tag, bool round) const
    {
        auto result = ScaleTo(this->value, tag);

        return !round ? result : roundf(result);
    }
}
