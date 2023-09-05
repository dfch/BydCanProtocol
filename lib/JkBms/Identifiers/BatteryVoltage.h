// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "CentiVoltVoltBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the battery voltage of the BMS.
    struct tagBatteryVoltage : CentiVoltBase
    {
        // Intentionally left blank.
    }

    /// @brief Represents the battery voltage of the BMS.
    using BatteryVoltage = tagBatteryVoltage;
}
