// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Contract.h>
#include <Word.h>
#include <TemperatureCelsius.h>

namespace JkBms::Identifiers
{
    using namespace Endian;
    using namespace Temperature;

    struct TemperatureRangeM40To100C
    {
        struct Getter
        {
            TemperatureCelsius operator()(Word word) const
            {
                auto value = word.ToLittleEndian();
                Contract::Expects([value]
                {
                    return value >= 0 && value <= 140;
                }, "TemperatureRangeM40To100C::Getter");

                const auto offset = 100;

                TemperatureCelsius result(value > 100 ? -1 * (value - offset) : value);

                return result;
            }
        };

        struct Setter
        {
            Word operator()(TemperatureCelsius value) const
            {
                auto v = value.GetValue();
                Contract::Expects([v] { return v > -40 && v <= 100; }, "TemperatureRangeM40To100C::Setter");

                return Word(v);
            }
        };
    };
}
