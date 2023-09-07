// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "VoltBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Balance Start Voltage of the BMS.
    using BalanceStartVoltage = tagVoltBase<2000, 4500, Scale::Milli>;
}
