// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace JkBms
{
    /// @brief Represents the identiier of the JK-BMS RS485 protocol. 
    /// Note: update std::set<Id> as well when modifying this enum.
    enum class Id : uint8_t
    {
        ReadAll = 0x00, // Only allowed in combination with CommandWord::ReadAll.
        CellVoltage = 0x79, // defined:N
        BmsTemperature = 0x80, // defined:2
        BatteryBoxTemperature = 0x81, // defined:2
        BatteryTemperature = 0x82, // defined:2
        BatteryVoltage = 0x83, // defined:2
        BatteryCurrent = 0x84, // defined:2
        BatteryChargeState = 0x85, // defined:1
        BatteryTemperatureSensorsCount = 0x86, // defined:1
        BatteryCycleCount = 0x87, // defined:2
        BatteryChargeTotal = 0x89, // defined:4
        BatteryStringCount = 0x8a, // defined:2
        BatteryWarningInformation = 0x8b,
        BatteryStatusInformation = 0x8c,
        OverVoltageProtection = 0x8e, // defined:2
        UnderVoltageProtection = 0x8f, // defined:2
        CellOverVoltageProtection = 0x90, // defined:2
        CellOverVoltageRecovery = 0x91, // defined:2
        CellOverVoltageProtectionDelay = 0x92, // defined:2
        CellUnderVoltageProtection = 0x93, // defined:2
        CellUnderVoltageRecovery = 0x94, // defined:2
        CellUnderVoltageProtectionDelay = 0x95, // defined:2
        CellVoltageDifferenceProtection = 0x96, // defined:2
        DischargeOverCurrentProtection = 0x97, // defined:2
        DischargeOverCurrentDelay = 0x98, // defined:2
        ChargeOverCurrentProtection = 0x99, // defined:2
        ChargeOverCurrentDelay = 0x9a, // defined:2
        BalanceStartVoltage = 0x9b, // defined:2
        BalanceStartVoltageDifference = 0x9c, // defined:2
        BalancerActiveFlag = 0x9d, // defined:1
        MosfetTemperatureProtection = 0x9e, // defined:2
        MosfetTemperatureRecovery = 0x9f, // defined:2
        BatteryBoxTemperatureProtection = 0xa0, // defined:2
        BatteryBoxTemperatureRecovery = 0xa1, // defined:2
        BatteryTemperatureDifferenceProtection = 0xa2, // defined:2
        BatteryHighChargeTemperatureProtection = 0xa3,
        BatteryHighDischargeTemperatureProtection = 0xa4,
        ChargeLowTemperatureProtection = 0xa5, // defined:2
        ChargeLowTemperatureRecovery = 0xa6, // defined:2
        DischargeLowTemperatureProtection = 0xa7,
        DischargeLowTemperatureRecovery = 0xa8,
        BatteryCellCount = 0xa9,
        BatteryCapacity = 0xaa, // defined:4
        BmsAllowToChargeFlag = 0xab,
        BmsAllowToDischargeFlag = 0xac,
        BatteryCurrentCalibration = 0xad,
        BmsAddress = 0xae,
        BatteryType = 0xaf,
        SleepWaitTime = 0xB0,
        LowCapacityAlarmThreshold = 0xB1,
        BmsModifyPassword = 0xB2,
        BmsForceToChargeFlag = 0xB3,
        ProductId = 0xB4,
        ManufacturerDate = 0xB5,
        TotalUptime = 0xB6,
        FirmareVersion = 0xB7,
        CalibrationFlag = 0xB8,
        BatteryChargeActual = 0xB9,
        ManufacturerId = 0xBA,
        SystemRestart = 0xBB,
        SystemRestore = 0xBC,
        RemoteUpgradeFlag = 0xBD,
        BatteryLowVoltageShutdown = 0xBE, // defined:2
        BatteryLowVoltageRecovery = 0xBF, // defined:2
        ProtocolVersion = 0xC0,
    };
}
