// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include "Rs485.h"

#include <cstddef>

#include "Frame.h"
#include "Identifiers/CellVoltage.h"
#include "Identifiers/PowerManagementTemperature.h"


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
                case Id::PowerManagementTemperature:
                    messages[id] = unit;
                    index += sizeof(Identifiers::PowerManagementTemperature);
                    break;
                default:
                    frame = ValidationResult::InvalidIdentifier;
                    return;
            }
        }
    }
}
