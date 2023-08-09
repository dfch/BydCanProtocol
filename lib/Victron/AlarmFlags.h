/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstddef>

namespace Victron
{
    /// @brief Represents the alarm flags.
    typedef enum alarmFlags : size_t
    {
        HighBatteryVoltageAlarm = 2,
        LowBatteryVoltageAlarm = 4,
        HighTemperatureAlarm = 6,
        LowTemperatureAlarm = 0 +8,
        HighChargeTemperatureAlarm = 2 +8,
        LowChargeTemperatureAlarm = 4 +8,
        HighDischargeCurrentAlarm = 6 +8,
        HighChargeCurrentAlarm = 0 +8 +8,
        InternalFailureAlarm = 6 +8 +8,
        CellImbalanceAlarm = 0 +8 +8 +8,
    } AlarmFlags;
}
