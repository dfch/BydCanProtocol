// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "MilliVoltBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Cell under Voltage Protection recovery of the BMS.
    struct tagCellUnderVoltageRecovery : MilliVoltBase
    {
        // Intentionally left blank.
    }

    /// @brief Represents the Cell under Voltage Protection recovery of the BMS.
    using CellUnderVoltageRecovery = tagCellUnderVoltageRecovery;
}
