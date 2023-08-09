/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

namespace Units
{
    /// @brief Represents a scale.
    enum class Scale
    {
        Default = 0, // No conversion
        Nano, // 10^-9
        Micro, // 10^-6
        Milli, // 10^-3
        Centi, // 10^-2
        Percent, // 10^-2
        Deci, // 10^-1
        Deka, // 10^1
        Hecto, // 10^2
        Kilo, // 10^3
        Myria, // 10^4
        Mega, // 10^6
        Giga, // 10^9
        Tera, // 10^12
    };
}
