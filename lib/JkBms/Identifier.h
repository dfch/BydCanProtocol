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
                Id::PowerManagementTemperature,
                Id::BatteryBoxTemperature,
                Id::BatteryTemperature,
                Id::BatteryVoltage,
                Id::BatteryCurrent,
                Id::RemainingBatteryCapacity,
                Id::BatteryTemperatureSensorsCount,
                Id::BatteryCycleCount,
                Id::TotalBatteryCycleCapacity,
                Id::TotalNumberOfBatterySeries,
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
                Id::ActiveBalanceSwitch,
                Id::PowerManagementTemperatureProtection,
                Id::PowerManagementTemperatureRecovery,
                Id::InternalBatteryBoxTemperatureProtection,
                Id::InternalBatteryBoxTemperatureRecovery,
                Id::BatteryTemperatureProtection,
                Id::BatteryTemperatureRecovery,
                Id::BatteryTemperatureProtectionDelay,
                Id::MaximumChargingVoltage,
                Id::MinimumDischargeVoltage,
                Id::BalanceVoltage,
                Id::TemperatureSensorCalibration,
                Id::TotalCapacityCalibration,
                Id::TemperatureProtection,
                Id::TemperatureProtectionRecovery,
                Id::ManufacturerId,
                Id::SystemRestart,
                Id::SystemReset,
                Id::RemoteUpgrade,
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
