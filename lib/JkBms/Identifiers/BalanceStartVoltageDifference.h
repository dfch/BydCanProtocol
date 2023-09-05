// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "MilliVoltBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Balance Start Voltage Difference of the BMS.
    struct tagBalanceStartVoltageDifference : MilliVoltBase
    {
        // Intentionally left blank.
    }

    /// @brief Represents the Balance Start Voltage Difference of the BMS.
    using BalanceStartVoltageDifference = tagBalanceStartVoltageDifference;
}
