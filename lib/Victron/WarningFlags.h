// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>

namespace Victron
{
    /// @brief Represents the warning flags.
    typedef enum warningFlags : size_t
    {
        HighBatteryVoltageWarning = 2,
        LowBatteryVoltageWarning = 4,
        HighTemperatureWarning = 6,
        LowTemperatureWarning = 0 +8,
        HighChargeTemperatureWarning = 2 +8,
        LowChargeTemperatureWarning = 4 +8,
        HighDischargeCurrentWarning = 6 +8,
        HighChargeCurrentWarning = 0 +8 +8,
        InternalFailureWarning = 6 +8 +8,
        CellImbalanceWarning = 0 +8 +8 +8,
    } WarningFlags;
}
