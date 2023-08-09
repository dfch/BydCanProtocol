/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

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
}
