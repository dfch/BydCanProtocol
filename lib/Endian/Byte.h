/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace Endian
{
    #pragma pack(push, 1)
    /// @brief Represents a BYTE.
    union tagByte
    {
        uint8_t Value;
    };
    #pragma pack(pop)

    using Byte = tagByte;
}
