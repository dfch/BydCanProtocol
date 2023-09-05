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
                    messages[id] = unit;
                    // We can use any struct with a size of 1 + Identifier byte here.
                    index += sizeof(Identifiers::RemainingBatteryCapacity);
                    break;

                // Handling of structs with size 2 + Identifier.
                case Id::PowerManagementTemperature:
                case Id::InternalBatteryBoxTemperature:
                case Id::BatteryTemperature:
                case Id::BatteryVoltage:
                case Id::CurrentData:
                case Id::OverVoltageProtection:
                case Id::UnderVoltageProtection:
                case Id::CellOverVoltageProtection:
                case Id::CellOverVoltageRecovery:
                case Id::CellUnderVoltageProtection:
                case Id::CellUnderVoltageRecovery:
                case Id::CellVoltageDifferenceProtection:
                case Id::BalanceStartVoltage:
                case Id::MaximumChargingVoltage:
                case Id::MinimumDischargeVoltage:
                case Id::BatteryLowVoltageShutdown:
                case Id::BatteryLowVoltageRecovery:
                case Id::CellOverVoltageProtectionDelay:
                case Id::CellUnderVoltageProtectionDelay:
                    messages[id] = unit;
                    // We can use any struct with a size of 2 + Identifier bytes here.
                    index += sizeof(Identifiers::PowerManagementTemperature);
                    break;

                // Handling of structs with size 4 + Identifier.
                case Id::TotalBatteryCycleCapacity:
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
