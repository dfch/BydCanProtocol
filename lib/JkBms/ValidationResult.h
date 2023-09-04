// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace JkBms
{
    enum class ValidationResult : uint8_t
    {
        Success = 0x00,
        NotParsed,
        FrameTooShort,
        InvalidHeader,
        InvalidLength,
        InvalidIdentifier,
        InvalidEndCode,
        InvalidChecksum,
    };
}
