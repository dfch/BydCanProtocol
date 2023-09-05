// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "CentiVoltVoltBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the under Voltage Protection of the BMS.
    struct tagUnderVoltageProtection : CentiVoltBase
    {
        // Intentionally left blank.
    }

    /// @brief Represents the under Voltage Protection of the BMS.
    using UnderVoltageProtection = tagUnderVoltageProtection;
}
