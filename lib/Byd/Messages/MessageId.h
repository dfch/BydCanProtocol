/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace Byd
{
    /// @brief Represents the message id.
    enum class MessageId : uint32_t
    {
        Invalid = 0x000, // Not a valid message id.
        Dvcc = 0x351, 
        StateInfo = 0x355,
        BatteryStats = 0x356,
        AlarmsWarnings = 0x35A,
        EventsUnused = 0x35B,
        ManufacturerInfo = 0x35E,
        BatteryInfo = 0x35F,
        Unknown0 = 0x360,
        BankInfo = 0x372,
        CellInfo = 0x373,
        CellVoltMinId = 0x374,
        CellVoltMaxId = 0x375,
        CellTempMinId = 0x376,
        CellTempMaxId = 0x377,
        History = 0x378,
        BatterySize = 0x379,
        ProductInfo = 0x382,
    };
}
