/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

#include <Volt.h>
#include <Ampere.h>

namespace Victron
{
    /// @brief Represents the DVCC information.
    class Dvcc
    {
        public:
            /// @brief Represents the maximum charge voltage (CVL).
            Units::Volt ChargeVoltageLimit;
            /// @brief Represents the maximum discharge voltage (DVL).
            Units::Volt DischargeVoltageLimit;
            /// @brief Represents the maximum charge current (CCL).
            Units::Ampere ChargeCurrentLimit;
            /// @brief Represents the maximum discharge current (DCL).
            Units::Ampere DischargeCurrentLimit;
            
    };
}
