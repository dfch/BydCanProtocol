// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <set>
#include <cstdint>

#include "Id.h"

namespace JkBms
{
    #pragma pack(push, 1)
    struct tagIdentifier
    {
        Id Value;

        /// @brief Determines whether the specified contents of Identifier is valid or not.
        /// @return True, if the contents of Identifier is valid; false, otherwise.
        bool IsValid() const noexcept 
        {
            static const std::set<Id> Values 
            {
                Id::ReadAll,
                Id::CellVoltage,
                Id::BmsTemperature,
                Id::BatteryBoxTemperature,
                Id::BatteryTemperature,
                Id::BatteryVoltage,
                Id::BatteryCurrent,
                Id::BatteryChargeState,
                Id::BatteryTemperatureSensorsCount,
                Id::BatteryCycleCount,
                Id::BatteryChargeTotal,
                Id::BatteryStringCount,
                Id::BatteryWarningInformation,
                Id::BatteryStatusInformation,
                Id::OverVoltageProtection,
                Id::UnderVoltageProtection,
                Id::CellOverVoltageProtection,
                Id::CellOverVoltageRecovery,
                Id::CellOverVoltageProtectionDelay,
                Id::CellUnderVoltageProtection,
                Id::CellUnderVoltageRecovery,
                Id::CellUnderVoltageProtectionDelay,
                Id::CellVoltageDifferenceProtection,
                Id::DischargeOverCurrentProtection,
                Id::DischargeOverCurrentDelay,
                Id::ChargeOverCurrentProtection,
                Id::ChargeOverCurrentDelay,
                Id::BalanceStartVoltage,
                Id::BalanceStartVoltageDifference,
                Id::BalancerActiveFlag,
                Id::MosfetTemperatureProtection,
                Id::MosfetTemperatureRecovery,
                Id::BatteryBoxTemperatureProtection,
                Id::BatteryBoxTemperatureRecovery,
                Id::BatteryTemperatureDifferenceProtection,
                Id::BatteryHighChargeTemperatureProtection,
                Id::BatteryHighDischargeTemperatureProtection,
                Id::ChargeLowTemperatureProtection,
                Id::ChargeLowTemperatureRecovery,
                Id::DischargeLowTemperatureProtection,
                Id::DischargeLowTemperatureRecovery,
                Id::BatteryCellCount,
                // Id::TemperatureProtection,
                Id::BatteryCapacity,
                Id::BmsAllowToDischargeFlag,
                Id::ManufacturerId,
                Id::SystemRestart,
                Id::SystemRestore,
                Id::RemoteUpgradeFlag,
                Id::BatteryLowVoltageShutdown,
                Id::BatteryLowVoltageRecovery,
                Id::ProtocolVersion,
            };

            return Values.contains(Value);
        }
    };
    #pragma pop

    using Identifier = tagIdentifier;
}
