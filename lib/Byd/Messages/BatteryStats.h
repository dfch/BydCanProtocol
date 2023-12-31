// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Byd
{
    /// @brief Represents the battery statistics.
    typedef struct tagBatteryStats
    {
        /// @brief Represents the battery voltage in centi Volt.
        uint16_t VoltageCentiVolt;
        /// @brief Represents the battery current in deci Ampere.
        int16_t CurrentDeciAmpere;
        /// @brief Represents the battery temperature in deci Celsius.
        int16_t TemperatureDeciCelsius;
        /// @brief Unused.
        uint16_t Reserved0;
    } BatteryStats;

    static_assert(DataLength == sizeof(BatteryStats), "sizeof(BatteryStats) must be equal to DataLength.");
}
