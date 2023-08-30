/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents the raw data of int64_t.
    struct tagInt64s
    {
        int64_t E0;
    };
    #pragma pack(pop)
    
    using Int64s = tagInt64s;
}
