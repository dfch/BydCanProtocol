/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace JkBms
{
    enum class ValidationResult : uint8_t
    {
        Success = 0x00,
        FrameTooShort,
        InvalidHeader,
        InvalidLength,
        InvalidIdentifier,
        InvalidEndCode,
        InvalidChecksum,
    };
}
