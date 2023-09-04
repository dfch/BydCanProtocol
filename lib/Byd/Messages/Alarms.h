// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <bitset>

namespace Byd
{
    /// @brief Represents the alarm and warning flags.
    typedef struct tagAlarms
    {
        /// @brief Represents the alarm flags.
        std::bitset<32> Alarm;
        /// @brief Represents the warning flags.
        std::bitset<32> Warning;
    } Alarms;

    static_assert(DataLength == sizeof(Alarms), "sizeof(Alarms) must be equal to DataLength.");
}
