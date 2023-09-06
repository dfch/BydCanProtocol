// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include "Rs485.h"

#include <cstddef>

#include "Frame.h"
#include "Identifiers/CellVoltage.h"
#include "Identifiers/PowerManagementTemperature.h"
#include "Identifiers/RemainingBatteryCapacity.h"
#include "Identifiers/TotalBatteryCycleCapacity.h"

namespace JkBms
{
    using std::uint8_t;

    void Rs485::ParseMessages(uint8_t &data, size_t size) noexcept
    {
        auto index = &data;
        while (index < &data + size)
        {
            auto unit = reinterpret_cast<InformationUnit*>(index);
            auto id = unit->Identifier.Value;
            switch (id)
            {
                case Id::CellVoltage:
                {
                    auto cellVoltage = reinterpret_cast<Identifiers::CellVoltage*>(index);
                    messages[id] = unit;
                    index += cellVoltage->Length + 
                        sizeof(Identifiers::CellVoltage::Identifier) + 
                        sizeof(Identifiers::CellVoltage::Length);
                    break;
                }
                
                // Handling of structs with size 1 + Identifier.
                case Id::RemainingBatteryCapacity:
                case Id::BatteryTemperatureSensorsCount:
                case Id::ActiveBalanceSwitch:
                    messages[id] = unit;
                    // We can use any struct with a size of 1 + Identifier byte here.
                    index += sizeof(Identifiers::RemainingBatteryCapacity);
                    break;

                // Handling of structs with size 2 + Identifier.
                case Id::PowerManagementTemperature:
                case Id::BatteryBoxTemperature:
                case Id::BatteryTemperature:
                case Id::BatteryVoltage:
                case Id::BatteryCurrent:
                case Id::BatteryCycleCount:
                case Id::BatteryStringCount:
                case Id::OverVoltageProtection:
                case Id::UnderVoltageProtection:
                case Id::CellOverVoltageProtection:
                case Id::CellOverVoltageRecovery:
                case Id::CellOverVoltageProtectionDelay:
                case Id::CellUnderVoltageProtection:
                case Id::CellUnderVoltageRecovery:
                case Id::CellUnderVoltageProtectionDelay:
                case Id::CellVoltageDifferenceProtection:
                case Id::DischargeOverCurrentProtection:
                case Id::DischargeOverCurrentDelay:
                case Id::ChargeOverCurrentProtection:
                case Id::ChargeOverCurrentDelay:
                case Id::BalanceStartVoltage:
                case Id::MaximumChargingVoltage:
                case Id::MinimumDischargeVoltage:
                case Id::BatteryLowVoltageShutdown:
                case Id::BatteryLowVoltageRecovery:
                    messages[id] = unit;
                    // We can use any struct with a size of 2 + Identifier bytes here.
                    index += sizeof(Identifiers::PowerManagementTemperature);
                    break;

                // Handling of structs with size 4 + Identifier.
                case Id::TotalBatteryCycleCapacity:
                case Id::BatteryCapacity:
                    messages[id] = unit;
                    // We can use any struct with a size of 4 + Identifier bytes here.
                    index += sizeof(Identifiers::TotalBatteryCycleCapacity);
                    break;

                default:
                    frame = ValidationResult::InvalidIdentifier;
                    return;
            }
        }
    }
}
