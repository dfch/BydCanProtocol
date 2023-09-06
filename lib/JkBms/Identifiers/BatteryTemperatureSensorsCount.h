// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Byte.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;

    #pragma pack(push, 1)
    /// @brief Represents the Battery Temperature Sensors Count of the BMS.
    struct tagBatteryTemperatureSensorsCount
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The number of sensors.
        Byte Value;

    };
    #pragma pack(pop)

    /// @brief Represents the Battery Temperature Sensors Count of the BMS.
    using BatteryTemperatureSensorsCount = tagBatteryTemperatureSensorsCount;
}
