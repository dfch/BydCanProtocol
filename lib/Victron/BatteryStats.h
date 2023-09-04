// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

#include "../Temperature/TemperatureCelsius.h"
#include <Volt.h>
#include <WattHour.h>
#include <Ampere.h>

namespace Victron
{
    /// @brief Represents the battery statistics.
    class BatteryStats
    {
        public:
            /// @brief Represents the battery voltage.
            Units::Volt Voltage;
            /// @brief Represents the battery current.
            Units::Ampere Current;
            /// @brief Represents the amount of charged energy for the battery.
            Units::WattHour ChargedEnergy;
            /// @brief Represents the amount of discharged energy for the battery.
            Units::WattHour DischargedEnergy;
            /// @brief Represents the battery temperature.
            Temperature::TemperatureCelsius Temperature;

    };
}
