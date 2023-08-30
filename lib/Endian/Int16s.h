/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents the raw data of int16_t.
    struct tagInt16s
    {
        int16_t E0;
        int16_t E1;
        int16_t E2;
        int16_t E3;
    };
    #pragma pack(pop)
    
    using Int16s = tagInt16s;
}
