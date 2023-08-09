/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#include "Can.h"
using CanTwai::Can;
using CanTwai::Configuration;

#include "Message.h"
using Byd::Message;

#include <Contract.h>

namespace CanTwai
{

    Can::Can(twai_general_config_t* general , twai_timing_config_t* timing, twai_filter_config_t* filter)
    {
        assert(NULL != general);
        assert(NULL != timing);
        assert(NULL != filter);

        auto result = twai_driver_install(general, timing, filter);
        assert(ESP_OK == result);

        result = twai_start();
        assert(ESP_OK == result);
    }

    bool Can::EmulateBydBinary()
    {
        auto result = ESP_FAIL;

        twai_message_t message;

        const uint32_t address = 0x0000 & 0xF000;
        const uint32_t extendedFrameFormat = address & 0xF000 ? 1 : 0;

        message.identifier = address | 0x35E;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 'B';
        message.data[1] = 'Y';
        message.data[2] = 'D';
        message.data[3] = 0;
        message.data[4] = 0;
        message.data[5] = 0;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x382;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 'P';
        message.data[1] = 'R';
        message.data[2] = 'E';
        message.data[3] = 'M';
        message.data[4] = 'I';
        message.data[5] = 'U';
        message.data[6] = 'M';
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x35F;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 0x4C;
        message.data[1] = 0x69;
        message.data[2] = 0x01;
        message.data[3] = 0x17;
        message.data[4] = 0x69;
        message.data[5] = 0;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x35A;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        for (auto c = 0; c < message.data_length_code; c++) 
        {
            message.data[c] = 0xAA;
        }
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x35B;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        for (auto c = 0; c < message.data_length_code; c++) 
        {
            message.data[c] = 0x00;
        }
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x351;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 0x48;
        message.data[1] = 0x02;
        message.data[2] = 0x00;
        message.data[3] = 0x05;
        message.data[4] = 0x00;
        message.data[5] = 0x05;
        message.data[6] = 0xAE;
        message.data[7] = 0x01;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x355;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 0x43;
        message.data[1] = 0x00;
        message.data[2] = 0x64;
        message.data[3] = 0x00;
        message.data[4] = 0x56;
        message.data[5] = 0;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x356;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 0xBE;
        message.data[1] = 0x14;
        message.data[2] = 0xF9;
        message.data[3] = 0xFF;
        message.data[4] = 0x8C;
        message.data[5] = 0x00;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x360;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 1;
        message.data[1] = 0;
        message.data[2] = 2;
        message.data[3] = 0;
        message.data[4] = 3;
        message.data[5] = 0;
        message.data[6] = 4;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x372;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 0x2;
        message.data[1] = 0;
        message.data[2] = 0;
        message.data[3] = 0;
        message.data[4] = 0;
        message.data[5] = 0;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x373;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 0xEA;
        message.data[1] = 0x0C;
        message.data[2] = 0x01;
        message.data[3] = 0x0D;
        message.data[4] = 0x1F;
        message.data[5] = 0x01;
        message.data[6] = 0x22;
        message.data[7] = 0x01;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x374;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = '2';
        message.data[1] = 0;
        message.data[2] = 0;
        message.data[3] = 0;
        message.data[4] = 0;
        message.data[5] = 0;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x375;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = '2';
        message.data[1] = 0;
        message.data[2] = 0;
        message.data[3] = 0;
        message.data[4] = 0;
        message.data[5] = 0;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x376;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = '2';
        message.data[1] = 0;
        message.data[2] = 0;
        message.data[3] = 0;
        message.data[4] = 0;
        message.data[5] = 0;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x377;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = '1';
        message.data[1] = 0;
        message.data[2] = 0;
        message.data[3] = 0;
        message.data[4] = 0;
        message.data[5] = 0;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x378;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 0x40;
        message.data[1] = 0x08;
        message.data[2] = 0;
        message.data[3] = 0;
        message.data[4] = 0x2B;
        message.data[5] = 0x07;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        message.identifier = address | 0x379;
        message.extd = extendedFrameFormat;
        message.data_length_code = 8;
        message.data[0] = 0x9C;
        message.data[1] = 0;
        message.data[2] = 0;
        message.data[3] = 0;
        message.data[4] = 0;
        message.data[5] = 0;
        message.data[6] = 0;
        message.data[7] = 0;
        result = twai_transmit(&message, portMAX_DELAY); 

        return ESP_OK == result;
    }

    bool Can::EmulateByd()
    {
        auto result = ESP_FAIL;

        twai_message_t message;
        std::shared_ptr<Message> data;
        
        // ManufacturerInfo
        data = Message::Factory::CreateManufacturerInfo().at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // ProductInfo
        data = Message::Factory::CreateProductInfo().at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // BatteryInfo
        Victron::StateInfo stateInfo;
        stateInfo.StateOfCharge.Value.SetValue(0.67);
        stateInfo.StateOfHealth.Value.SetValue(1);
        stateInfo.SizeTotalAmpereHour.Value.SetValue(156);
        stateInfo.SizeAvailableAmpereHour.Value.SetValue(105);
        data = Message::Factory::CreateBatteryInfo(stateInfo).at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // AlarmsWarnings
        Victron::AlarmWarning alarms;
        alarms.Reset();
        alarms.SetAlarm(Victron::AlarmFlags::CellImbalanceAlarm);
        alarms.SetWarning(Victron::WarningFlags::HighBatteryVoltageWarning);
        data = Message::Factory::CreateAlarmWarning(alarms).at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // EventsUnused
        data = Message::Factory::CreateEventsUnused().at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // Dvcc
        Victron::Dvcc dvcc;
        dvcc.ChargeVoltageLimit.Value.SetValue(58.4);
        dvcc.DischargeCurrentLimit.Value.SetValue(43);
        dvcc.ChargeCurrentLimit.Value.SetValue(128);
        dvcc.DischargeCurrentLimit.Value.SetValue(128);
        data = Message::Factory::CreateDvcc(dvcc).at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // StateInfo
        data = Message::Factory::CreateStateInfo(stateInfo).at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // BatteryStats
        Victron::BatteryStats batteryStats;
        batteryStats.Voltage.Value.SetValue(53.1);
        batteryStats.Current.Value.SetValue(-0.7);
        batteryStats.ChargedEnergy.Value.SetValue(211200);
        batteryStats.DischargedEnergy.Value.SetValue(183500);
        batteryStats.Temperature.SetValue(18);
        data = Message::Factory::CreateBatteryStats(batteryStats).at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // Unknown0
        data = Message::Factory::CreateUnknown0().at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // BankInfo
        Victron::BankInfo bankInfo;
        bankInfo.Total.Value.SetValue(2);
        bankInfo.Offline.Value.SetValue(0);
        data = Message::Factory::CreateBankInfo(bankInfo).at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // CellInfo
        Victron::CellInfo cellInfo;
        cellInfo.CellVoltageMinimum.Value.SetValue(3.306);
        cellInfo.CellVoltageMaximum.Value.SetValue(3.329);
        cellInfo.CellTemperaureMinimum.SetValue(14);
        cellInfo.CellTemperaureMaximum.SetValue(17);
        cellInfo.CellVoltageMinimumName = "2";
        cellInfo.CellVoltageMaximumName = "2";
        cellInfo.CellTemperaureMinimumName = "2";
        cellInfo.CellTemperaureMaximumName = "1";
        auto v = Message::Factory::CreateCellInfo(cellInfo);
        Contract::Requires([v] { return 5 == v.size(); });

        data = v.at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 
        data = v.at(1);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 
        data = v.at(2);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 
        data = v.at(3);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 
        data = v.at(4);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // History
        data = Message::Factory::CreateHistory(batteryStats).at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        // BatterySize
        data = Message::Factory::CreateBatterySize(stateInfo).at(0);
        message = CreateMessage(data);
        result = twai_transmit(&message, portMAX_DELAY); 

        return ESP_OK == result;
    }

    twai_message_t Can::CreateMessage(std::shared_ptr<Byd::Message> data)
    {
        Contract::Requires([data] { return nullptr != data; });

        twai_message_t result;

        auto raw = data->SerialiseData();
        
        result.extd = 0;
        result.identifier = (uint32_t) data->Id;

        auto bytesCopied = raw.Bytes.CopyTo(result.data, sizeof(result.data), true);
        Contract::Requires([bytesCopied] { return Byd::DataLength == bytesCopied; });
        result.data_length_code = bytesCopied;

        return result;
    }

    std::shared_ptr<Can> Can::Factory::Create(twai_general_config_t* general, twai_timing_config_t* timing, twai_filter_config_t* filter)
    {
        assert(NULL != general);
        assert(NULL != timing);
        assert(NULL != filter);

        auto result = std::make_shared<Can>(general, timing, filter);

        return result;
    }

    std::shared_ptr<Can> Can::Factory::Create(std::shared_ptr<Configuration> configuration)
    {
        assert(NULL != configuration);

        auto result = Can::Factory::Create(&configuration->General, &configuration->Timing, &configuration->Filter);

        return result;
    }
}

#endif
