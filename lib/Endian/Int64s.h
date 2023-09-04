// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

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
