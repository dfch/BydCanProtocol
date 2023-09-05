// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "MilliVoltBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Balance Voltage of the BMS.
    struct tagBalanceVoltage : MilliVoltBase
    {
        // Intentionally left blank.
    }

    /// @brief Represents the Balance Voltage of the BMS.
    using BalanceVoltage = tagBalanceVoltage;
}
