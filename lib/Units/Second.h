// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "ValueT.h"

namespace Units
{
    using namespace std;

    using ToSeconds = std::ratio<1>;
    using ToMinutes = ratio_multiply<ratio<60, 1>, ToSeconds>;
    using ToHours = ratio_multiply<ratio<60, 1>, ToMinutes>;
    using ToDays = ratio_multiply<ratio<24, 1>, ToHours>;

    using FromSeconds = std::ratio<1>;
    using FromMinutes = ratio_multiply<ratio<60, 1>, ToSeconds>;
    using FromHours = ratio_multiply<ratio<60, 1>, ToMinutes>;
    using FromDays = ratio_multiply<ratio<24, 1>, ToHours>;

    using MicroSecond = ValueT<float, micro>;
    using MilliSecond = ValueT<float, milli>;
    using Second = ValueT<float, std::ratio<1>>;
    using Minute = ValueT<float, FromMinutes>;
    using Hour = ValueT<float, FromHours>;
    using Day = ValueT<float, FromDays>;
}
