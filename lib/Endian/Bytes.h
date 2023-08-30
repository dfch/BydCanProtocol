/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace Endian
{
   #pragma pack(push, 1)
    struct tagBytes
    {
        uint8_t Byte0;
        uint8_t Byte1;

        /// @brief Converts the value to little endian.
        /// @return The converted value in little endian.
        inline uint16_t ToLittleEndian() const noexcept 
        {
            return Byte0 << 1*8 | 
                Byte1; 
        }
    };
    #pragma pack(pop)

    using Bytes = tagBytes;
}
