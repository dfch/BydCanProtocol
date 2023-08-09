/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace Byd
{
    /// @brief Represents the battery bank information.
    typedef struct tagBankInfo
    {
        /// @brief Represents the number of batteries in total.
        uint16_t Total;
        /// @brief Represents the number of batteries offline.
        uint16_t Offline;
        /// @brief Represents the number of batteries which are blocked for charging.
        uint16_t DischargingBlocked;    ///< Not supported, always 0.
        /// @brief Represents the number of batteries which are blocked for discharging.
        uint16_t ChargingBlocked;       ///< Not supported, always 0.
    } BankInfo;

    static_assert(DataLength == sizeof(BankInfo), "sizeof(BankInfo) must be equal to DataLength");
}
