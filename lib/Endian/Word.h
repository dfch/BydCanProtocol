// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

#include "Bytes.h"

namespace Endian
{
     #pragma pack(push, 1)
    /// @brief Represents a WORD in Big Endian.
    union tagWord
    {
        uint16_t Value;
        Bytes Values;

        /// @brief Converts the value to little endian.
        /// @return The converted value in little endian.
        inline uint16_t ToLittleEndian() const noexcept 
        {
            return Value << 1*8 | 
                Value >> 1*8; 
        }
    };
    #pragma pack(pop)

    using Word = tagWord;
}
