// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Byd
{
    /// @brief Represents the battery information.
    typedef struct tagBatteryInfo
    {
        /// @brief Represents the product id.
        uint16_t ProductId;
        /// @brief Represents the firmware version.
        uint16_t Firmware;
        /// @brief Represents available capacity in Ampere hours.
        uint16_t SizeAvailableAmpereHour;
        uint16_t Reserved0;
    } BatteryInfo;

    static_assert(DataLength == sizeof(BatteryInfo), "DataLength must be equal to sizeof(BatteryInfo).");
}
