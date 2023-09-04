// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Byd
{
    /// @brief Represents the state information of the battery.
    typedef struct tagStateInfo
    {
        /// @brief Represents the state of charge in percent.
        uint16_t SocPercent;
        /// @brief Represents the state of health in percent.
        uint16_t SohPercent;
        /// @brief Unused.
        uint32_t Reserved0;
    } StateInfo;

    static_assert(DataLength == sizeof(StateInfo), "sizeof(StateInfo) must be equal to DateLength.");
}
