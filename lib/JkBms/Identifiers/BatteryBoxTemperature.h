// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "TemperatureBase.h"

namespace JkBms::Identifiers
{

    #pragma pack(push, 1)
    /// @brief Represents the internal temperature (-40°C to 100°C).
    /// The temperature is represented via a mapping scheme that spans from -40°C to 100°C. 
    /// The range is represented by integers from 0 to 140. 
    /// Values above 100 represent negative temperatures; values below 100 represent positive temperaures. 
    /// For example, a value of 101 corresponds to -1°C.
    struct tagBatteryBoxTemperature : public TemperatureBase
    {
        // Intentionally left blank.
    };
    #pragma pack(pop)

    /// @brief Represents the internal temperature (-40°C to 100°C).
    /// The temperature is represented via a mapping scheme that spans from -40°C to 100°C. 
    /// The range is represented by integers from 0 to 140. 
    /// Values above 100 represent negative temperatures; values below 100 represent positive temperaures. 
    /// For example, a value of 101 corresponds to -1°C.
    using BatteryBoxTemperature = tagInternalBatteryBoxTemperature;
}
