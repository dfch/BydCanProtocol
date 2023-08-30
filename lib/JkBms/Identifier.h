/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <set>
#include <cstdint>

namespace JkBms
{
    /// @brief Represents the identiier of the JK-BMS RS485 protocol.
    enum class Id : uint8_t
    {
        ReadAll = 0x00, // Only allowed in combination with CommandWord::ReadAll.
        CellVoltage = 0x79, // Read cell voltage.
        PowerTubeTemperature = 0x80, // Read power tube temperature.
        BatteryBoxTemperature = 0x81, // Read battery box temperature.
        BatteryTemperature = 0x82, // Read battery temperature.
        BatteryVoltage = 0x83, // Read battery voltage.
        CurrentData = 0x84, // Read current data.
        BatteryRemainingCapacity = 0x85, // Read battery remaining capacity.
        BatterySensorCount = 0x86, // Read battery sensor count.
        BatteryCycleCount = 0x87, // Read battery cycle count.
    };

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
                Id::PowerTubeTemperature,
                Id::BatteryBoxTemperature,
                Id::BatteryTemperature,
                Id::BatteryVoltage,
                Id::CurrentData,
                Id::BatteryRemainingCapacity,
                Id::BatterySensorCount,
                Id::BatteryCycleCount,
            };

            return Values.contains(Value);
        }
    };
    #pragma pop

    using Identifier = tagIdentifier;
}
