// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Contract.h>
#include <Byte.h>
#include <Percent.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace Endian;
    using namespace Units;

    /// @brief State of Charge (SOC). Represents the remaining battery capacity in percent (0..100).
    struct tagBatteryChargeState
    {
        JkBms::Identifier Identifier;
        
        Byte Value;

        Percent ToPercent() const
        {
            const auto full = 100;
            Contract::Expects([this] { return this->Value.Value <= full; });

            return Percent(this->Value.Value, Scale::Centi);
        };
    };

    /// @brief State of Charge (SOC). Represents the remaining battery capacity in percent (0..100).
    using BatteryChargeState = tagBatteryChargeState;
}
