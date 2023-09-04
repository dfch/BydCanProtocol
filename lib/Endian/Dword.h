// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

#include "Words.h"

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents a DWORD in Big Endian.
    union tagDword
    {
        uint32_t Value;
        Words Values;

        /// @brief Converts the value to little endian.
        /// @return The converted value in little endian.
        inline uint32_t ToLittleEndian() const noexcept
        {
            return ((Value & 0xFF000000) >> 3*8) |
                ((Value & 0x00FF0000) >> 1*8) |
                ((Value & 0x0000FF00) << 1*8) |
                ((Value & 0x000000FF) << 3*8);
        }
    };
    #pragma pack(pop)

    using Dword = tagDword;
}
