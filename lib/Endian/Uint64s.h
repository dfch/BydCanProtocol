/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents the raw data of uint64_t.
    struct tagUint64s
    {
        uint64_t E0;
    };
    #pragma pack(pop)
    
    using Uint64s = tagUint64s;
}
