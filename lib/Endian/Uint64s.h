// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

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
