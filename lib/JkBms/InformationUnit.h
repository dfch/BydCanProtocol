// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

#include "Identifier.h"

namespace JkBms
{
    #pragma pack(push, 1)
    /// @brief Basic body data unit of a frame.
    struct tagInformationUnit
    {
        Identifier Identifier;
        uint8_t* Data;
    };
    #pragma pack(pop)

    using InformationUnit = tagInformationUnit;
}
