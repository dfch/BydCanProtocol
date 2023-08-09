/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

#include "Constants.h"

namespace Byd
{
    /// @brief Represents the product information.
    typedef struct tagProductInfo
    {
        /// @brief Represents the product name.
        char Name[DataLength];
    } ProductInfo;

    static_assert(DataLength == sizeof(ProductInfo), "sizeof(ProductInfo) must be equal to DataLength.");
}
