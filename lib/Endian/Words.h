/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include "Word.h"

namespace Endian
{
    #pragma pack(push, 1)
    struct tagWords
    {
        Word Word0;
        Word Word1;

        /// @brief Converts the value to little endian.
        /// @return The converted value in little endian.
        inline uint32_t ToLittleEndian() const noexcept
        {
            return Word0.ToLittleEndian() << 2*8 | 
                Word1.ToLittleEndian(); 
        }
    };
    #pragma pack(pop)

    using Words = tagWords;
}
