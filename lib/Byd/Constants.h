// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <cstddef>

namespace Byd
{
    /// @brief The length of the data in bytes.
    constexpr size_t DataLength = 8;
    
    /// @brief Represents the BYD LVS Battery-Box Premium product identifier.
    constexpr uint16_t ProductId = 0x694C;
    /// @brief Represents the BYD LVS Battery-Box Premium firmware version.
    constexpr uint16_t FirmwareVersion = 0x1701;

    /// @brief Represents the BYD manufacturer name.
    constexpr char ManufacturerName[] = "BYD";
    /// @brief Represents the BYD product name.
    constexpr char ProductName[] = "PREMIUM";
}
