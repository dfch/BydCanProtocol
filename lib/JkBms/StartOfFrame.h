// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

#include <Bytes.h>

namespace JkBms
{
    using namespace Endian;

    /// @brief Magic value that identifies the start of a frame. Always 0x4E, 78d, 'N'.
    constexpr uint8_t HeaderValue0 = 0x4E;
    /// @brief Magic value that identifies the start of a frame. Always 0x57, 87d, 'W'.
    constexpr uint8_t HeaderValue1 = 0x57;

    #pragma pack(push, 1)
    /// @brief Signature of a frame with fixed values.
    struct tagStartOfFrame : Bytes
    {
        /// @brief Determines whether the specified contents of a StartOfFrame is valid or not.
        /// @return True, if the contents of StartOfFrame is valid; false, otherwise.
        bool IsValid() const noexcept { return HeaderValue0 == Byte0 && HeaderValue1 == Byte1; }
    };
    #pragma pack(pop)
    
    using StartOfFrame = tagStartOfFrame;
}
