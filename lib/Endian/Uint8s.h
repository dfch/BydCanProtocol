// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents the raw data of uint8_t.
    struct tagUint8s
    {
        uint8_t E0;
        uint8_t E1;
        uint8_t E2;
        uint8_t E3;
        uint8_t E4;
        uint8_t E5;
        uint8_t E6;
        uint8_t E7;
    };
    #pragma pack(pop)
    
    using Uint8s = tagUint8s;
}
