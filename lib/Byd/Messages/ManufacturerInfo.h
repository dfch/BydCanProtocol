/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

#include "Constants.h"

namespace Byd
{
    /// @brief Represents the manufacturer information.
    typedef struct tagManufacturer
    {
        /// @brief Represents the manufacturer name.
        char Name[DataLength];
    } ManufacturerInfo;

    static_assert(DataLength == sizeof(ManufacturerInfo), "sizeof(ManufacturerInfo) must be equal to DataLength.");
}
