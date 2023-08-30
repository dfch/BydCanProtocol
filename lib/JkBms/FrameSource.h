/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace JkBms
{
    /// @brief Represents the source of the information, such as BMS.
    enum class FrameSource : uint8_t
    {
        Bms = 0x00,
        Bluetooth = 0x01,
        Gps = 0x02, 
        Terminal = 0x03, // PC or computer.
    };
}
