// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents the raw data of bytes.
    struct tagStdBytes
    {
        std::byte E0;
        std::byte E1;
        std::byte E2;
        std::byte E3;
        std::byte E4;
        std::byte E5;
        std::byte E6;
        std::byte E7;
    };
    #pragma pack(pop)
    
    using StdBytes = tagStdBytes;
}
