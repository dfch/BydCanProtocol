/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents the raw data of int32_t.
    struct tagInt32s
    {
        int32_t E0;
        int32_t E1;
    };
    #pragma pack(pop)
    
    using Int32s = tagInt32s;
}
