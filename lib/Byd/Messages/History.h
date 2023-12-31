// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace Byd
{
    /// @brief Represents the history data of the battery.
    typedef struct tagHistory
    {
        /// @brief Represents the total amount of charged energy in hecto Watt hours.
        uint32_t ChargedEnergyHectoWattHour;
        /// @brief Represents the total amount of discharged energy in hecto Watt hours.
        uint32_t DischargedEnergyHectoWattHour;
    } History;

    static_assert(DataLength == sizeof(History), "sizeof(History) must be equal to DataLength.");
}
