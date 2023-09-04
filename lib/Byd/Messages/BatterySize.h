// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Byd
{
    /// @brief Represents the battery size.
    typedef struct tagBatterySize
    {
        /// @brief Represents the total amount of Ampere hours.
        uint16_t SizeTotalAmpereHour;
        /// @brief Unused.
        uint16_t Reserved0;
        /// @brief Unused.
        uint32_t Reserved1;
    } BatterySize;

    static_assert(DataLength == sizeof(BatterySize), "sizeof(BatterySize) must be equal to DataLength.");
}
