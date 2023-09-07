// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "TemperatureBase.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Power Management Temperature Protection (0°C to 100°C).
    using MosfetTemperatureProtection = tagTemperatureBase<0, 100>;
}
