/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace JkBms
{
    /// @brief Represents the identiier of the JK-BMS RS485 protocol. 
    /// Note: update std::set<Id> as well when modifying this enum.
    enum class Id : uint8_t
    {
        ReadAll = 0x00, // Only allowed in combination with CommandWord::ReadAll.
        CellVoltage = 0x79,
        PowerManagementTemperature = 0x80,
        InternalBatteryBoxTemperature = 0x81,
        BatteryTemperature = 0x82,
        BatteryVoltage = 0x83,
        CurrentData = 0x84,
        RemainingBatteryCapacity = 0x85,
        BatteryTemperatureSensorsCount = 0x86,
        BatteryCycleCount = 0x87,
        TotalBatteryCycleCapacity = 0x89,
        TotalNumberOfBatterySeries = 0x8a,
        BatteryWarningInformation = 0x8b,
        BatteryStatusInformation = 0x8c,
        OverVoltageProtection = 0x8e,
        UnderVoltageProtection = 0x8f,
        CellOverVoltageProtection = 0x90,
        CellOverVoltageRecovery = 0x91,
        CellOverVoltageProtectionDelay = 0x92,
        CellUnderVoltageProtection = 0x93,
        CellUnderVoltageRecovery = 0x94,
        CellUnderVoltageProtectionDelay = 0x95,
        CellVoltageDifferenceProtection = 0x96,
        DischargeOverCurrentProtection = 0x97,
        DischargeOverCurrentDelay = 0x98,
        ChargeOverCurrentProtection = 0x99,
        ChargeOverCurrentDelay = 0x9a,
        BalanceStartVoltage = 0x9b,
        BalanceStartVoltageDifference = 0x9c,
        ActiveBalanceSwitch = 0x9d,
        PowerManagementTemperatureProtection = 0x9e,
        PowerManagementTemperatureRecovery = 0x9f,
        InternalBatteryBoxTemperatureProtection = 0xa0,
        InternalBatteryBoxTemperatureRecovery = 0xa1,
        BatteryTemperatureProtection = 0xa2,
        BatteryTemperatureRecovery = 0xa3,
        BatteryTemperatureProtectionDelay = 0xa4,
        MaximumChargingVoltage = 0xa5,
        MinimumDischargeVoltage = 0xa6,
        BalanceVoltage = 0xa7,
        TemperatureSensorCalibration = 0xa8,
        TotalCapacityCalibration = 0xa9,
        TemperatureProtection = 0xaa,
        TemperatureProtectionRecovery = 0xab,
        ManufacturerId = 0xBA,
        SystemRestart = 0xBB,
        SystemReset = 0xBC,
        RemoteUpgrade = 0xBD,
        BatterLowVoltageShutdown = 0xBE,
        BatterLowVoltageRecovery = 0xBF,
        ProtocolVersion = 0xC0,
    };
}
