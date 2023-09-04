// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <string.h>

#include <Message.h>
#include <Messages/MessageId.h>
#include <Messages/Dvcc.h>
#include <CellInfo.h>

#include <Dvcc.h>

namespace test::envNative::test_Byd
{
    void CreateSucceeds()
    {
        // Arrange
        
        // Act
        auto sut = Byd::Message::Factory::Create();

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::Invalid, result->Id);
        
        auto data = std::get<Byd::Raw>(result->Data);

        TEST_ASSERT_EQUAL(0x00, data.Uint32s.E0);
        TEST_ASSERT_EQUAL(0x00, data.Uint32s.E1);
    }
        
    void CreateDvccSucceeds()
    {
        // Arrange
        Victron::Dvcc input;
        float cvl = 16 * 3.65;
        float ccl = 128.0;
        float dcl = 128.0;
        float dvl = 16 * 2.6875;
        input.ChargeVoltageLimit.Value.SetValue(cvl);
        input.DischargeVoltageLimit.Value.SetValue(dvl);
        input.ChargeCurrentLimit.Value.SetValue(ccl);
        input.DischargeCurrentLimit.Value.SetValue(dcl);
        
        // Act
        auto sut = Byd::Message::Factory::CreateDvcc(input);

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::Dvcc, result->Id);
        
        auto data = std::get<Byd::Dvcc>(result->Data);
        TEST_ASSERT_EQUAL(cvl *10, data.ChargeVoltageLimitDeciVolt);
        TEST_ASSERT_EQUAL(dvl *10, data.DischargeVoltageLimitDeciVolt);
        TEST_ASSERT_EQUAL(ccl *10, data.ChargeCurrentLimitDeciAmpere);
        TEST_ASSERT_EQUAL(dcl *10, data.DischargeCurrentLimitDeciAmpere);

        Byd::Raw raw;
        raw.Uint16s.E0 = data.ChargeVoltageLimitDeciVolt;
        TEST_ASSERT_EQUAL_HEX8(0x48, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x02, raw.Bytes.E1);

        raw.Uint16s.E0 = data.DischargeVoltageLimitDeciVolt;
        TEST_ASSERT_EQUAL_HEX8(0xAE, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x01, raw.Bytes.E1);

        raw.Uint16s.E0 = data.ChargeCurrentLimitDeciAmpere;
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x05, raw.Bytes.E1);

        raw.Uint16s.E0 = data.DischargeCurrentLimitDeciAmpere;
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x05, raw.Bytes.E1);

        // Assert
        for(auto c : result->SerialiseData().ByteArray)
        {
            printf("0x%02X ", (int) c & 0xFF);
        }
    }
        
    void CreateStateInfoSucceeds()
    {
        // Arrange
        Victron::StateInfo input;
        float soc = 0.67;
        float soh = 1.00;
        float total = 156;
        float available = 105;
        input.StateOfCharge.Value.SetValue(soc);
        input.StateOfHealth.Value.SetValue(soh);
        input.SizeTotalAmpereHour.Value.SetValue(total);
        input.SizeAvailableAmpereHour.Value.SetValue(available);
        
        // Act
        auto sut = Byd::Message::Factory::CreateStateInfo(input);

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::StateInfo, result->Id);
        
        auto data = std::get<Byd::StateInfo>(result->Data);
        TEST_ASSERT_EQUAL(soc * 100, data.SocPercent);
        TEST_ASSERT_EQUAL(soh * 100, data.SohPercent);

        Byd::Raw raw;

        raw.Uint16s.E0 = data.SocPercent;
        TEST_ASSERT_EQUAL_HEX8(0x43, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E1);

        raw.Uint16s.E0 = data.SohPercent;
        TEST_ASSERT_EQUAL_HEX8(0x64, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E1);
    }

    void CreateAlarmWarningSucceeds()
    {
        // Arrange
        Victron::AlarmWarning input;
        input.SetAlarm(Victron::AlarmFlags::HighBatteryVoltageAlarm);
        input.SetAlarm(Victron::AlarmFlags::LowBatteryVoltageAlarm);
        input.SetAlarm(Victron::AlarmFlags::HighTemperatureAlarm);
        input.SetAlarm(Victron::AlarmFlags::LowTemperatureAlarm);
        input.SetAlarm(Victron::AlarmFlags::HighChargeTemperatureAlarm);
        input.SetAlarm(Victron::AlarmFlags::LowChargeTemperatureAlarm);
        input.SetAlarm(Victron::AlarmFlags::HighDischargeCurrentAlarm);
        input.SetAlarm(Victron::AlarmFlags::HighChargeCurrentAlarm);
        input.SetAlarm(Victron::AlarmFlags::InternalFailureAlarm);
        input.SetAlarm(Victron::AlarmFlags::CellImbalanceAlarm);

        input.SetWarning(Victron::WarningFlags::HighBatteryVoltageWarning);
        input.SetWarning(Victron::WarningFlags::LowBatteryVoltageWarning);
        input.SetWarning(Victron::WarningFlags::HighTemperatureWarning);
        input.SetWarning(Victron::WarningFlags::LowTemperatureWarning);
        input.SetWarning(Victron::WarningFlags::HighChargeTemperatureWarning);
        input.SetWarning(Victron::WarningFlags::LowChargeTemperatureWarning);
        input.SetWarning(Victron::WarningFlags::HighDischargeCurrentWarning);
        input.SetWarning(Victron::WarningFlags::HighChargeCurrentWarning);
        input.SetWarning(Victron::WarningFlags::InternalFailureWarning);
        input.SetWarning(Victron::WarningFlags::CellImbalanceWarning);

        // Act
        auto sut = Byd::Message::Factory::CreateAlarmWarning(input);

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::AlarmsWarnings, result->Id);
        
        auto data = std::get<Byd::Alarms>(result->Data);

        printf("Alarms   %08X\n", data.Alarm.to_ulong());
        printf("Warnings %08X\n", data.Warning.to_ulong());

        Byd::Raw raw;

        raw.Uint32s.E0 = data.Alarm.to_ulong();
        TEST_ASSERT_EQUAL_HEX8(0x56, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x55, raw.Bytes.E1);
        TEST_ASSERT_EQUAL_HEX8(0x69, raw.Bytes.E2);
        TEST_ASSERT_EQUAL_HEX8(0xA9, raw.Bytes.E3);

        raw.Uint32s.E0 = data.Warning.to_ulong();
        TEST_ASSERT_EQUAL_HEX8(0x56, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x55, raw.Bytes.E1);
        TEST_ASSERT_EQUAL_HEX8(0x69, raw.Bytes.E2);
        TEST_ASSERT_EQUAL_HEX8(0xA9, raw.Bytes.E3);
    }
    
    void CreateEventsUnusedSucceeds()
    {
        // Arrange
        
        // Act
        auto sut = Byd::Message::Factory::CreateEventsUnused();

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::EventsUnused, result->Id);
        
        auto data = std::get<Byd::Raw>(result->Data);

        TEST_ASSERT_EQUAL(0x00, data.Uint32s.E0);
        TEST_ASSERT_EQUAL(0x00, data.Uint32s.E1);
    }
    
    void CreateBatteryInfoSucceeds()
    {
        // Arrange
        uint16_t productId = 0x694C;
        uint16_t firmware = 0x1701;
        Victron::StateInfo input;
        float soc = 0.67;
        float soh = 1.00;
        float total = 156;
        float available = 105;
        input.StateOfCharge.Value.SetValue(soc);
        input.StateOfHealth.Value.SetValue(soh);
        input.SizeTotalAmpereHour.Value.SetValue(total);
        input.SizeAvailableAmpereHour.Value.SetValue(available);
        
        // Act
        auto sut = Byd::Message::Factory::CreateBatteryInfo(input);

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::BatteryInfo, result->Id);
        
        auto data = std::get<Byd::BatteryInfo>(result->Data);
        TEST_ASSERT_EQUAL(productId, data.ProductId);
        TEST_ASSERT_EQUAL(firmware, data.Firmware);
        TEST_ASSERT_EQUAL(available, data.SizeAvailableAmpereHour);

        Byd::Raw raw;

        raw.Uint16s.E0 = data.ProductId;
        TEST_ASSERT_EQUAL_HEX8(0x4C, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x69, raw.Bytes.E1);

        raw.Uint16s.E0 = data.Firmware;
        TEST_ASSERT_EQUAL_HEX8(0x01, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x17, raw.Bytes.E1);

        raw.Uint16s.E0 = data.SizeAvailableAmpereHour;
        TEST_ASSERT_EQUAL_HEX8(0x69, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E1);
    }
    
    void CreateUnknown0Succeeds()
    {
        // Arrange
        
        // Act
        auto sut = Byd::Message::Factory::CreateUnknown0();

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::Unknown0, result->Id);
        
        auto data = std::get<Byd::Raw>(result->Data);

        TEST_ASSERT_EQUAL(0x00, data.Uint32s.E0);
        TEST_ASSERT_EQUAL(0x00, data.Uint32s.E1);
    }

    void CreateHistorySucceeds()
    {
        // Arrange
        Victron::BatteryStats input;
        float volt = 53.1;
        float ampere = -0.7;
        float temp = 14.0;
        float charged = 211200;
        float discharged = 183500;
        input.Voltage.Value.SetValue(volt);
        input.Current.Value.SetValue(ampere);
        input.Temperature.SetValue(temp);
        input.ChargedEnergy.Value.SetValue(charged);
        input.DischargedEnergy.Value.SetValue(discharged);
        
        // Act
        auto sut = Byd::Message::Factory::CreateHistory(input);

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::History, result->Id);
        
        auto data = std::get<Byd::History>(result->Data);
        TEST_ASSERT_EQUAL(charged /100, data.ChargedEnergyHectoWattHour);
        TEST_ASSERT_EQUAL(discharged /100, data.DischargedEnergyHectoWattHour);

        Byd::Raw raw;

        raw.Uint32s.E0 = data.ChargedEnergyHectoWattHour;
        TEST_ASSERT_EQUAL_HEX8(0x40, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x08, raw.Bytes.E1);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E2);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E3);

        raw.Uint32s.E0 = data.DischargedEnergyHectoWattHour;
        TEST_ASSERT_EQUAL_HEX8(0x2B, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x07, raw.Bytes.E1);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E2);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E3);
    }
    
    void CreateBatterySizeSucceeds()
    {
        // Arrange
        Victron::StateInfo input;
        float soc = 0.67;
        float soh = 1.00;
        float total = 156;
        float available = 105;
        input.StateOfCharge.Value.SetValue(soc);
        input.StateOfHealth.Value.SetValue(soh);
        input.SizeTotalAmpereHour.Value.SetValue(total);
        input.SizeAvailableAmpereHour.Value.SetValue(available);
        
        // Act
        auto sut = Byd::Message::Factory::CreateBatterySize(input);

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::BatterySize, result->Id);
        
        auto data = std::get<Byd::BatterySize>(result->Data);
        TEST_ASSERT_EQUAL(total, data.SizeTotalAmpereHour);

        Byd::Raw raw;

        raw.Uint16s.E0 = data.SizeTotalAmpereHour;
        TEST_ASSERT_EQUAL_HEX8(0x9C, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E1);
    }

    void CreateBankInfoSucceeds()
    {
        // Arrange
        Victron::BankInfo input;
        float total = 2;
        float offline = 0;
        float charging = 0;
        float discharging = 0;
        input.Total.Value.SetValue(total);
        input.Offline.Value.SetValue(offline);
        input.ChargingBlocked.Value.SetValue(charging);
        input.DischargingBlocked.Value.SetValue(discharging);
        
        // Act
        auto sut = Byd::Message::Factory::CreateBankInfo(input);

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::BankInfo, result->Id);
        
        auto data = std::get<Byd::BankInfo>(result->Data);
        TEST_ASSERT_EQUAL(total, data.Total);
        TEST_ASSERT_EQUAL(offline, data.Offline);
        TEST_ASSERT_EQUAL(charging, data.ChargingBlocked);
        TEST_ASSERT_EQUAL(discharging, data.DischargingBlocked);

        Byd::Raw raw;

        raw.Uint16s.E0 = data.Total;
        TEST_ASSERT_EQUAL_HEX8(0x02, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E1);

        raw.Uint16s.E0 = data.Offline;
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E1);

        raw.Uint16s.E0 = data.ChargingBlocked;
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E1);

        raw.Uint16s.E0 = data.DischargingBlocked;
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E1);
    }

    void CreateCellInfoSucceeds()
    {
        // Arrange
        Victron::CellInfo input;
        float voltageMinimum = 3.306;
        float voltageMaximum = 3.329;
        float temperatureMinimum = 14;
        float temperatureMaximum = 17;
        std::string cellVoltageMinimumName = "2";
        std::string cellVoltageMaximumName = "2";
        std::string cellTemperatureMinimumName = "2";
        std::string cellTemperatureMaximumName = "1";
        input.CellVoltageMinimum.Value.SetValue(voltageMinimum);
        input.CellVoltageMaximum.Value.SetValue(voltageMaximum);
        input.CellTemperaureMinimum.SetValue(temperatureMinimum);
        input.CellTemperaureMaximum.SetValue(temperatureMaximum);
        input.CellVoltageMinimumName = cellVoltageMinimumName;
        input.CellVoltageMaximumName = cellVoltageMaximumName;
        input.CellTemperaureMinimumName = cellTemperatureMinimumName;
        input.CellTemperaureMaximumName = cellTemperatureMaximumName;

        // Act
        auto sut = Byd::Message::Factory::CreateCellInfo(input);

        // Assert
        TEST_ASSERT_EQUAL(5, sut.size());

        // Test CellInfo.
        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::CellInfo, result->Id);

        auto data = std::get<Byd::CellInfo>(result->Data);
        TEST_ASSERT_EQUAL(voltageMinimum *1000, data.CellVoltageMinimumMilliVolt);
        TEST_ASSERT_EQUAL(voltageMaximum *1000, data.CellVoltageMaximumMilliVolt);
        TEST_ASSERT_EQUAL(temperatureMinimum +273.15, data.CellTemperatureMinimumKelvin);
        TEST_ASSERT_EQUAL(temperatureMaximum +273.15, data.CellTemperatureMaximumKelvin);

        Byd::Raw raw {};

        raw.Uint16s.E0 = data.CellVoltageMinimumMilliVolt;
        TEST_ASSERT_EQUAL_HEX8(0xEA, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x0C, raw.Bytes.E1);
        
        raw.Uint16s.E0 = data.CellVoltageMaximumMilliVolt;
        TEST_ASSERT_EQUAL_HEX8(0x01, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x0D, raw.Bytes.E1);
        
        raw.Uint16s.E0 = data.CellTemperatureMinimumKelvin;
        TEST_ASSERT_EQUAL_HEX8(0x1F, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x01, raw.Bytes.E1);
        
        raw.Uint16s.E0 = data.CellTemperatureMaximumKelvin;
        TEST_ASSERT_EQUAL_HEX8(0x22, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x01, raw.Bytes.E1);

        // Test CellId VoltageMin.
        result = sut.at(1);
        TEST_ASSERT_EQUAL(Byd::MessageId::CellVoltMinId, result->Id);

        auto cellId = std::get<Byd::CellId>(result->Data);
        TEST_ASSERT_EQUAL_STRING(cellVoltageMinimumName.c_str(), cellId.Name);

        strcpy(raw.CharArray, cellId.Name);
        TEST_ASSERT_EQUAL_HEX8('2', raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E1);
        // TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E2);

        // Test CellId VoltageMax.
        result = sut.at(2);
        TEST_ASSERT_EQUAL(Byd::MessageId::CellVoltMaxId, result->Id);

        cellId = std::get<Byd::CellId>(result->Data);
        TEST_ASSERT_EQUAL_STRING(cellVoltageMaximumName.c_str(), cellId.Name);

        strcpy(raw.CharArray, cellId.Name);
        TEST_ASSERT_EQUAL_HEX8('2', raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E1);
        // TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E2);

        // Test CellId TempMin.
        result = sut.at(3);
        TEST_ASSERT_EQUAL(Byd::MessageId::CellTempMinId, result->Id);

        cellId = std::get<Byd::CellId>(result->Data);
        TEST_ASSERT_EQUAL_STRING(cellTemperatureMinimumName.c_str(), cellId.Name);

        strcpy(raw.CharArray, cellId.Name);
        TEST_ASSERT_EQUAL_HEX8('2', raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E1);
        // TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E2);

        // Test CellId TempMax.
        result = sut.at(4);
        TEST_ASSERT_EQUAL(Byd::MessageId::CellTempMaxId, result->Id);

        cellId = std::get<Byd::CellId>(result->Data);
        TEST_ASSERT_EQUAL_STRING(cellTemperatureMaximumName.c_str(), cellId.Name);

        strcpy(raw.CharArray, cellId.Name);
        TEST_ASSERT_EQUAL_HEX8('1', raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E1);
        // TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E2);
    }
    
    void CreateBatteryStatsSucceeds()
    {
        // Arrange
        Victron::BatteryStats input;
        float volt = 53.1;
        float ampere = -0.7;
        float temp = 14.0;
        float charged = 211200;
        float discharged = 183500;
        input.Voltage.Value.SetValue(volt);
        input.Current.Value.SetValue(ampere);
        input.Temperature.SetValue(temp);
        input.ChargedEnergy.Value.SetValue(charged);
        input.DischargedEnergy.Value.SetValue(discharged);
        
        // Act
        auto sut = Byd::Message::Factory::CreateBatteryStats(input);

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::BatteryStats, result->Id);
        
        auto data = std::get<Byd::BatteryStats>(result->Data);
        TEST_ASSERT_EQUAL(volt *100, data.VoltageCentiVolt);
        TEST_ASSERT_EQUAL(ampere *10, data.CurrentDeciAmpere);
        TEST_ASSERT_EQUAL(temp *10, data.TemperatureDeciCelsius);

        Byd::Raw raw;

        raw.Uint16s.E0 = data.VoltageCentiVolt;
        TEST_ASSERT_EQUAL_HEX8(0xBE, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x14, raw.Bytes.E1);

        raw.Uint16s.E0 = data.CurrentDeciAmpere;
        TEST_ASSERT_EQUAL_HEX8(0xF9, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0xFF, raw.Bytes.E1);

        raw.Uint16s.E0 = data.TemperatureDeciCelsius;
        TEST_ASSERT_EQUAL_HEX8(0x8C, raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8(0x00, raw.Bytes.E1);
    }
    
    void CreateManufacturerInfoSucceeds()
    {
        // Arrange
        constexpr char expected[] = "BYD";
        
        // Act
        auto sut = Byd::Message::Factory::CreateManufacturerInfo();

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::ManufacturerInfo, result->Id);
        
        auto data = std::get<Byd::ManufacturerInfo>(result->Data);
        TEST_ASSERT_EQUAL_STRING(expected, data.Name);

        Byd::Raw raw;

        strcpy(raw.CharArray, data.Name);
        TEST_ASSERT_EQUAL_HEX8('B', raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8('Y', raw.Bytes.E1);
        TEST_ASSERT_EQUAL_HEX8('D', raw.Bytes.E2);
        TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E3);
        // TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E4);
        // TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E5);
        // TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E6);
        // TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E7);
    }
    
    void CreateProductInfoSucceeds()
    {
        // Arrange
        constexpr char expected[] = "PREMIUM";
        
        // Act
        auto sut = Byd::Message::Factory::CreateProductInfo();

        // Assert
        TEST_ASSERT_EQUAL(1, sut.size());

        auto result = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::ProductInfo, result->Id);
        
        auto data = std::get<Byd::ProductInfo>(result->Data);
        TEST_ASSERT_EQUAL_STRING(expected, data.Name);

        Byd::Raw raw;

        strcpy(raw.CharArray, data.Name);
        TEST_ASSERT_EQUAL_HEX8('P', raw.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8('R', raw.Bytes.E1);
        TEST_ASSERT_EQUAL_HEX8('E', raw.Bytes.E2);
        TEST_ASSERT_EQUAL_HEX8('M', raw.Bytes.E3);
        TEST_ASSERT_EQUAL_HEX8('I', raw.Bytes.E4);
        TEST_ASSERT_EQUAL_HEX8('U', raw.Bytes.E5);
        TEST_ASSERT_EQUAL_HEX8('M', raw.Bytes.E6);
        TEST_ASSERT_EQUAL_HEX8('\0', raw.Bytes.E7);
    }
    
    void SerialiseDataSucceeds()
    {
        // Arrange
        constexpr char expected[] = "PREMIUM";
        auto sut = Byd::Message::Factory::CreateProductInfo();
        TEST_ASSERT_EQUAL(1, sut.size());
        auto message = sut.at(0);
        TEST_ASSERT_EQUAL(Byd::MessageId::ProductInfo, message->Id);
        
        // Act
        auto result = message->SerialiseData();

        // Assert
        TEST_ASSERT_EQUAL_STRING(expected, result.CharArray);
        TEST_ASSERT_EQUAL_HEX8('P', result.Bytes.E0);
        TEST_ASSERT_EQUAL_HEX8('R', result.Bytes.E1);
        TEST_ASSERT_EQUAL_HEX8('E', result.Bytes.E2);
        TEST_ASSERT_EQUAL_HEX8('M', result.Bytes.E3);
        TEST_ASSERT_EQUAL_HEX8('I', result.Bytes.E4);
        TEST_ASSERT_EQUAL_HEX8('U', result.Bytes.E5);
        TEST_ASSERT_EQUAL_HEX8('M', result.Bytes.E6);
        TEST_ASSERT_EQUAL_HEX8('\0', result.Bytes.E7);
    }
    
    void DataCopyToSmallerSucceeds()
    {
        // Arrange
        auto sizeExpected = 6;
        std::byte destination[6];
        memset(destination, 0xAA, sizeof(destination));
        
        Byd::Raw raw;
        raw.Bytes.E0 = std::byte( 0x48 );
        raw.Bytes.E1 = std::byte( 0x02 );
        raw.Bytes.E2 = std::byte( 0x00 );
        raw.Bytes.E3 = std::byte( 0x05 );
        raw.Bytes.E4 = std::byte( 0x00 );
        raw.Bytes.E5 = std::byte( 0x05 );
        raw.Bytes.E6 = std::byte( 0xAE );
        raw.Bytes.E7 = std::byte( 0x01 );
        
        // Act
        auto result = raw.Bytes.CopyTo(destination, sizeof(destination), true);

        // Assert
        TEST_ASSERT_EQUAL(sizeExpected, result);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E0, destination[0]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E1, destination[1]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E2, destination[2]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E3, destination[3]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E4, destination[4]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E5, destination[5]);
    }
    
    void DataCopyToEqualSucceeds()
    {
        // Arrange
        auto sizeExpected = 8;
        std::byte destination[8];
        memset(destination, 0xAA, sizeof(destination));

        Byd::Raw raw;
        raw.Bytes.E0 = std::byte( 0x48 );
        raw.Bytes.E1 = std::byte( 0x02 );
        raw.Bytes.E2 = std::byte( 0x00 );
        raw.Bytes.E3 = std::byte( 0x05 );
        raw.Bytes.E4 = std::byte( 0x00 );
        raw.Bytes.E5 = std::byte( 0x05 );
        raw.Bytes.E6 = std::byte( 0xAE );
        raw.Bytes.E7 = std::byte( 0x01 );
        
        // Act
        auto result = raw.Bytes.CopyTo(destination, sizeof(destination), true);

        // Assert
        TEST_ASSERT_EQUAL(sizeExpected, result);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E0, destination[0]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E1, destination[1]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E2, destination[2]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E3, destination[3]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E4, destination[4]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E5, destination[5]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E6, destination[6]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E7, destination[7]);
    }
    
    void DataCopyToLargerNoinitSucceeds()
    {
        // Arrange
        auto sizeExpected = 8;
        std::byte destination[10];
        memset(destination, 0xAA, sizeof(destination));
        
        Byd::Raw raw;
        raw.Bytes.E0 = std::byte( 0x48 );
        raw.Bytes.E1 = std::byte( 0x02 );
        raw.Bytes.E2 = std::byte( 0x00 );
        raw.Bytes.E3 = std::byte( 0x05 );
        raw.Bytes.E4 = std::byte( 0x00 );
        raw.Bytes.E5 = std::byte( 0x05 );
        raw.Bytes.E6 = std::byte( 0xAE );
        raw.Bytes.E7 = std::byte( 0x01 );
        
        // Act
        auto result = raw.Bytes.CopyTo(destination, sizeof(destination), false);

        // Assert
        TEST_ASSERT_EQUAL(8, result);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E0, destination[0]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E1, destination[1]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E2, destination[2]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E3, destination[3]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E4, destination[4]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E5, destination[5]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E6, destination[6]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E7, destination[7]);
        // TEST_ASSERT_EQUAL_HEX8(0xAA, destination[8]);
        TEST_ASSERT_EQUAL_HEX8(0xAA, destination[9]);
    }
    
    void DataCopyToLargerInitSucceeds()
    {
        // Arrange
        auto sizeExpected = 8;
        std::byte destination[10];
        memset(destination, 0xAA, sizeof(destination));
        
        Byd::Raw raw;
        raw.Bytes.E0 = std::byte( 0x48 );
        raw.Bytes.E1 = std::byte( 0x02 );
        raw.Bytes.E2 = std::byte( 0x00 );
        raw.Bytes.E3 = std::byte( 0x05 );
        raw.Bytes.E4 = std::byte( 0x00 );
        raw.Bytes.E5 = std::byte( 0x05 );
        raw.Bytes.E6 = std::byte( 0xAE );
        raw.Bytes.E7 = std::byte( 0x01 );
        
        // Act
        auto result = raw.Bytes.CopyTo(destination, sizeof(destination), true);

        // Assert
        TEST_ASSERT_EQUAL(sizeExpected, result);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E0, destination[0]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E1, destination[1]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E2, destination[2]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E3, destination[3]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E4, destination[4]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E5, destination[5]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E6, destination[6]);
        TEST_ASSERT_EQUAL_HEX8(raw.Bytes.E7, destination[7]);
        TEST_ASSERT_EQUAL_HEX8(0x00, destination[8]);
        TEST_ASSERT_EQUAL_HEX8(0x00, destination[9]);
    }
}
