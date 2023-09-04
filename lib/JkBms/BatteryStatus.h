// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace JkBms
{
    enum class BatteryStatus : uint8_t
    {
        ChargingOn = 1 << 0,   // 0th bit: Charging MOSFET state is ON
        ChargingOff = 0 << 0,  // 0th bit: Charging MOSFET state is OFF

        DischargingOn = 1 << 1,   // 1st bit: Discharging MOSFET state is ON
        DischargingOff = 0 << 1,  // 1st bit: Discharging MOSFET state is OFF

        BalancingOn = 1 << 2,   // 2nd bit: Balancing switch state is ON
        BalancingOff = 0 << 2,  // 2nd bit: Balancing switch state is OFF

        BatteryConnected = 1 << 3,   // 3rd bit: Battery is connected
        BatteryDisconnected = 0 << 3 // 3rd bit: Battery is disconnected
    };
}
