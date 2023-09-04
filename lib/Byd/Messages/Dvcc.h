// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Byd
{
    /// @brief Represents the DVCC information.
    typedef struct tagDvcc
    {
        /// @brief Represents the charge voltage limit in deci Volts (CVL).
        uint16_t ChargeVoltageLimitDeciVolt;
        /// @brief Represents the charge current limit in deci Amperes (CCL).
        uint16_t ChargeCurrentLimitDeciAmpere;
        /// @brief Represents the discharge current limit in deci Amperes (DCL).
        uint16_t DischargeCurrentLimitDeciAmpere;
        /// @brief Represents the discharge voltage limit in deci Volts (DVL).
        uint16_t DischargeVoltageLimitDeciVolt;
    } Dvcc;

    static_assert(DataLength == sizeof(Dvcc), "sizeof(Dvcc) must be equal to DataLength.");
}
