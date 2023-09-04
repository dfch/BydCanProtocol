// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents the raw data of int8_t.
    struct tagInt8s
    {
        int8_t E0;
        int8_t E1;
        int8_t E2;
        int8_t E3;
        int8_t E4;
        int8_t E5;
        int8_t E6;
        int8_t E7;
    };
    #pragma pack(pop)
    
    using Int8s = tagInt8s;
}
