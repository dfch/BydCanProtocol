// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents the raw data of uint16_t.
    struct tagUint16s
    {
        uint16_t E0;
        uint16_t E1;
        uint16_t E2;
        uint16_t E3;
    };
    #pragma pack(pop)
    
    using Uint16s = tagUint16s;
}
