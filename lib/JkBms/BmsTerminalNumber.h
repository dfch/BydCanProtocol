// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

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
