// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Contract
{
    #define NAMEOF(name) #name

    /// @brief Defines error codes to be used when following an escalation policy.
    enum class ErrorCode : uint16_t
    {
        ErrorSuccess = 0, // Indicates no error. Not used.
        Default = 1, // Default value for error codes.
        InvalidArgument = Default, // Error code used when encountering invalid arguments.
        NullArgument, // Error code when encountering null arguments.
        OutOfRange, // Error code when encountering out of range arguments.
    };
}
