/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace Byd
{
    /// @brief Represents the cell information.
    typedef struct tagCellInfo
    {
        /// @brief Represents the minimum cell voltage in milli Volt.
        uint16_t CellVoltageMinimumMilliVolt;
        /// @brief Represents the maximum cell voltage in milli Volt.
        uint16_t CellVoltageMaximumMilliVolt;
        /// @brief Represents the minimum cell temperature in Kelvin.
        uint16_t CellTemperatureMinimumKelvin;
        /// @brief Represents the maximum cell temperature in Kelvin.
        uint16_t CellTemperatureMaximumKelvin;
    } CellInfo;
}
