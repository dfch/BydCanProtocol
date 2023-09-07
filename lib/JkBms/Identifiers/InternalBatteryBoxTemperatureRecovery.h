// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "TemperatureBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Internal Battery Box Temperature Recovery temperature (40°C to 100°C).
    using BatteryBoxTemperatureRecovery = tagTemperatureBase<40, 100>;
}
