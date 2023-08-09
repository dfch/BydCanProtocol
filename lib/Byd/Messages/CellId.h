/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

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
}
