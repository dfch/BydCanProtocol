/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

#include <Word.h>

namespace JkBms
{
    using namespace Endian;

    #pragma pack(push, 1)
    /// @brief Represents the BMS terminal number.
    struct tagBmsTerminalNumber
    {
        Word NumberWordLow;
        uint8_t NumberByteHigh;
        uint8_t ManagementSparePart; // Always 0x00.
    };
    #pragma pack(pop)

    using BmsTerminalNumber = tagBmsTerminalNumber;
}
