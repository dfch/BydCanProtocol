// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace JkBms
{
    enum class StatusFlags : uint16_t 
    {
        LowCapacityAlarm = 0x0001,
        MOSFETOverTemp = 0x0002,
        ChargeOverVoltage = 0x0004,
        DischargeUnderVoltage = 0x0008,
        BatteryOverTemp = 0x0010,
        ChargeOverCurrent = 0x0020,
        DischargeOverCurrent = 0x0040,
        CellVoltageDifference = 0x0080,
        InternalOverTemp = 0x0100,
        LowTempAlarm = 0x0200,
        SingleCellOverVoltage = 0x0400,
        SingleCellUnderVoltage = 0x0800,
        Protect309_A = 0x1000,
        Protect309_B = 0x2000,
        Reserved1 = 0x4000,
        Reserved2 = 0x8000
    };

}
