// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "TemperatureBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Battery Temperature Protection temperature (5°C to 20°C).
    using BatteryTemperatureDifferenceProtection = tagTemperatureBase<5, 20>;
}
