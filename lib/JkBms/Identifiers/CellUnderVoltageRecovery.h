// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Scale.h>
#include "VoltBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Cell under Voltage Protection recovery of the BMS.
    using CellUnderVoltageRecovery = tagVoltBase<0, 150'000, Scale::Milli>;
}
