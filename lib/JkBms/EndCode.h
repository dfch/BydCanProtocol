/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace JkBms
{
    /// @brief Magic value that identifies the end part of the variable body part of a frame.
    constexpr uint8_t EndCodeValue0 = 0x68;

    #pragma pack(push, 1)
    /// @brief Signature of the end part of the variable body part of a frame.
    struct tagEndCode
    {
        uint8_t Value0; // Always 0x68, 104d, 'h'.

        /// @brief Determines whether the specified contents of a EndCode is valid or not.
        /// @return True, if the contents of EndCode is valid; false, otherwise.
        bool IsValid() const noexcept { return EndCodeValue0 == Value0; }
    };
    #pragma pack(pop)

    using EndCode = tagEndCode;
}
