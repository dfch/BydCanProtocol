// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "CentiVoltVoltBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Battery Low Voltage Recovery of the BMS.
    struct tagBatteryLowVoltageRecovery : CentiVoltBase
    {
        // Intentionally left blank.
    }

    /// @brief Represents the Battery Low Voltage Recovery of the BMS.
    using BatteryLowVoltageRecovery = tagBatteryLowVoltageRecovery;
}
