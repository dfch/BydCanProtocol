/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents the raw data of uint32_t.
    struct tagUint32s
    {
        uint32_t E0;
        uint32_t E1;
    };
    #pragma pack(pop)
    
    using Uint32s = tagUint32s;
}
