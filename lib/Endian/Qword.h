// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <cstddef>

#include <Contract.h>

#include "StdBytes.h"
#include "Uint8s.h"
#include "Int8s.h"
#include "Uint16s.h"
#include "Int16s.h"
#include "Uint32s.h"
#include "Int32s.h"
#include "Uint64s.h"
#include "Int64s.h"
#include "Byte.h"
#include "Bytes.h"
#include "Word.h"
#include "Words.h"
#include "Dword.h"
#include "Dwords.h"

namespace Endian
{
    inline bool IsLittleEndian() noexcept 
    { 
        uint8_t expected = 1;
        uint32_t actual = expected;

        auto result = reinterpret_cast<uint8_t*>(&actual)[0];

        return expected == result;
    }
    
    #pragma pack(push, 1)
    /// @brief Represents the raw data of different types.
    union tagQword
    {
        uint64_t Value;
        Dwords Values;

        /// @brief Converts the value to little endian.
        /// @return The converted value in little endian.
        inline uint64_t ToLittleEndian() const noexcept
        {
            return ((Value & 0xFF00000000000000ull) >> 7*8) |
                ((Value & 0x00FF000000000000ull) >> 5*8) |
                ((Value & 0x0000FF0000000000ull) >> 3*8) |
                ((Value & 0x000000FF00000000ull) >> 1*8) |
                ((Value & 0x00000000FF000000ull) << 1*8) |
                ((Value & 0x0000000000FF0000ull) << 3*8) |
                ((Value & 0x000000000000FF00ull) << 5*8) |
                ((Value & 0x00000000000000FFull) << 7*8);
        }

        StdBytes Bytes;
        Uint8s Uint8s;
        Int8s Int8s;
        Uint16s Uint16s;
        Int16s Int16s;
        Uint32s Uint32s;
        Int32s Int32s;
        Uint64s Uint64s;
        Int64s Int64s;
        
        std::byte ByteArray[sizeof(uint64_t)];
        unsigned char UcharArray[sizeof(uint64_t)];
        char CharArray[sizeof(uint64_t)];

    };
    #pragma pack(pop)

    using Qword = tagQword;

    // Ensure that we have proper byte packing and only occupy 64 bits.
    static_assert(sizeof(Qword) == sizeof(uint64_t), "Qword is not 64 bits.");
}
