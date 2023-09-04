// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

#include "Constants.h"

namespace Byd
{
    /// @brief Represents the cell identifier.
    typedef struct tagCellId
    {
        /// @brief The name of the cell.
        char Name[DataLength];
    } CellId;

    static_assert(DataLength == sizeof(CellId), "sizeof(CellId) must be equal to DataLength."); 
}
