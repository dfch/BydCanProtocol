// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "VoltBase.h"
#include "Scale.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Battery Low Voltage Shutdown of the BMS.
    using BatteryLowVoltageShutdown = VoltBase<0, 4500, Scale::Milli>;
}
