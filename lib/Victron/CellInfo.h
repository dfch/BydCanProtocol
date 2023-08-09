/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>
#include <cstring>

#include "../Temperature/TemperatureCelsius.h"
#include <Volt.h>

namespace Victron
{
    /// @brief Represents the battery cell information.
    class CellInfo
    {
        public:
            /// @brief Represents the minimum cell voltage.
            Units::Volt CellVoltageMinimum;
            /// @brief Represents the maximum cell voltage.
            Units::Volt CellVoltageMaximum;
            /// @brief Represents the minimum cell temperature.
            Temperature::TemperatureCelsius CellTemperaureMinimum;
            /// @brief Represents the maximum cell temperature.
            Temperature::TemperatureCelsius CellTemperaureMaximum;
            /// @brief Represents the name of the cell with the minimum voltage.
            std::string CellVoltageMinimumName;
            /// @brief Represents the name of the cell with the maximum voltage.
            std::string CellVoltageMaximumName;
            /// @brief Represents the name of the cell with the minimum temperature.
            std::string CellTemperaureMinimumName;
            /// @brief Represents the name of the cell with the maximum temperature.
            std::string CellTemperaureMaximumName;

    };
}
