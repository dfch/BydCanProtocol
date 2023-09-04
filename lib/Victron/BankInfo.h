// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Victron
{
    /// @brief Represents the battery bank information.
    class BankInfo
    {
        public:
            /// @brief Represents the number of batteries in total.
            Units::Unit Total;
            /// @brief Represents the number of batteries offline.
            Units::Unit Offline;
            /// @brief Represents the number of batteries which are blocked for charging.
            Units::Unit ChargingBlocked;
            /// @brief Represents the number of batteries which are blocked for discharging.
            Units::Unit DischargingBlocked;
    };
}
