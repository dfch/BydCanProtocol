/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <cassert>

#include "Message.h"
#include "Constants.h"
#include "Contract.h"
#include <algorithm>

namespace Byd
{
    std::vector<std::shared_ptr<Message>> Message::Factory::Create()
    {
        Message message;

        message.Id = MessageId::Invalid;

        Raw v;
        v.Int32s.E0 = 0;
        v.Int32s.E1 = 0;
        message.Data = v;

        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateDvcc(Victron::Dvcc& data)
    {
        Message message;
        
        message.Id = MessageId::Dvcc;

        Dvcc v;
        v.ChargeVoltageLimitDeciVolt = (std::uint16_t) data.ChargeVoltageLimit.Value.ScaleTo(Units::Scale::Deci, true);
        v.DischargeVoltageLimitDeciVolt = (std::uint16_t) data.DischargeVoltageLimit.Value.ScaleTo(Units::Scale::Deci, true);
        v.ChargeCurrentLimitDeciAmpere = (std::uint16_t) data.ChargeCurrentLimit.Value.ScaleTo(Units::Scale::Deci, true);
        v.DischargeCurrentLimitDeciAmpere = (std::uint16_t) data.DischargeCurrentLimit.Value.ScaleTo(Units::Scale::Deci, true);
        message.Data = v;

        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateStateInfo(Victron::StateInfo& data)
    {
        Message message;

        message.Id = MessageId::StateInfo;
        
        StateInfo v;
        v.SocPercent = data.StateOfCharge.Value.ScaleTo(Units::Scale::Percent, true);
        v.SohPercent = data.StateOfHealth.Value.ScaleTo(Units::Scale::Percent, true);
        v.Reserved0 = 0x0;
        message.Data = v;
        
        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateAlarmWarning(Victron::AlarmWarning& data)
    {
        using Victron::AlarmFlags;
        using Victron::WarningFlags;

        constexpr uint32_t AlarmsOk = 0xAAAAAAAA;
        constexpr uint32_t WarningsOk = AlarmsOk;

        Message message;

        message.Id = MessageId::AlarmsWarnings;

        Alarms v;
        v.Alarm = AlarmsOk;
        v.Warning = WarningsOk;

        // Set alarm flags and reset 0XAA bits.
        constexpr AlarmFlags alarms[] = 
        { 
            AlarmFlags::HighBatteryVoltageAlarm, 
            AlarmFlags::LowBatteryVoltageAlarm, 
            AlarmFlags::HighTemperatureAlarm, 
            AlarmFlags::LowTemperatureAlarm, 
            AlarmFlags::HighChargeTemperatureAlarm, 
            AlarmFlags::LowChargeTemperatureAlarm, 
            AlarmFlags::HighDischargeCurrentAlarm, 
            AlarmFlags::HighChargeCurrentAlarm, 
            AlarmFlags::InternalFailureAlarm, 
            AlarmFlags::CellImbalanceAlarm, 
        };

        for(auto item : alarms)
        {
            if(data.HasAlarm(item))
            {
                v.Alarm.flip(item);
                v.Alarm.flip(item +1);
            }
        }

        // Set warning flags and reset 0XAA bits.
        constexpr WarningFlags warnings[] = 
        { 
            WarningFlags::HighBatteryVoltageWarning, 
            WarningFlags::LowBatteryVoltageWarning, 
            WarningFlags::HighTemperatureWarning, 
            WarningFlags::LowTemperatureWarning, 
            WarningFlags::HighChargeTemperatureWarning, 
            WarningFlags::LowChargeTemperatureWarning, 
            WarningFlags::HighDischargeCurrentWarning, 
            WarningFlags::HighChargeCurrentWarning, 
            WarningFlags::InternalFailureWarning, 
            WarningFlags::CellImbalanceWarning, 
        };

        for(auto item : warnings)
        {
            if(data.HasWarning(item))
            {
                v.Warning.flip(item);
                v.Warning.flip(item +1);
            }
        }

        message.Data = v;

        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateEventsUnused()
    {
        Message message;

        message.Id = MessageId::EventsUnused;

        Raw v;
        v.Int32s.E0 = 0;
        v.Int32s.E1 = 0;
        message.Data = v;

        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateBatteryInfo(Victron::StateInfo& data)
    {
        Message message;

        message.Id = MessageId::BatteryInfo;

        BatteryInfo v;
        v.ProductId = ProductId;
        v.Firmware = FirmwareVersion;
        v.SizeAvailableAmpereHour = data.SizeAvailableAmpereHour.Value.GetValue();
        v.Reserved0 = 0x0;
        message.Data = v;

        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateUnknown0()
    {
        Message message;

        message.Id = MessageId::Unknown0;

        Raw v;
        v.Int32s.E0 = 0;
        v.Int32s.E1 = 0;
        message.Data = v;
        
        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateHistory(Victron::BatteryStats& data)
    {
        Message message;

        message.Id = MessageId::History;

        History v;
        v.ChargedEnergyHectoWattHour = data.ChargedEnergy.Value.ScaleTo(Units::Scale::Hecto, true);
        v.DischargedEnergyHectoWattHour = data.DischargedEnergy.Value.ScaleTo(Units::Scale::Hecto, true);
        message.Data = v;
        
        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateBatterySize(Victron::StateInfo &data)
    {
        Message message;

        message.Id = MessageId::BatterySize;
        
        BatterySize v;
        v.SizeTotalAmpereHour = data.SizeTotalAmpereHour.Value.GetValue();
        v.Reserved0 = 0x0;
        v.Reserved1 = 0x0;
        message.Data = v;
        
        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateBankInfo(Victron::BankInfo& data)
    {
        Message message;

        message.Id = MessageId::BankInfo;
        
        BankInfo v;
        v.Total = data.Total.Value.GetValue();
        v.Offline = data.Offline.Value.GetValue();
        v.ChargingBlocked = data.ChargingBlocked.Value.GetValue();
        v.DischargingBlocked = data.DischargingBlocked.Value.GetValue();
        message.Data = v;
        
        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateCellInfo(Victron::CellInfo& data)
    {
        Message message0;

        message0.Id = MessageId::CellInfo;
        
        CellInfo v;
        v.CellVoltageMinimumMilliVolt = data.CellVoltageMinimum.Value.ScaleTo(Units::Scale::Milli, true);
        v.CellVoltageMaximumMilliVolt = data.CellVoltageMaximum.Value.ScaleTo(Units::Scale::Milli, true);
        v.CellTemperatureMinimumKelvin = static_cast<Temperature::TemperatureKelvin>(data.CellTemperaureMinimum).GetValue();
        v.CellTemperatureMaximumKelvin = static_cast<Temperature::TemperatureKelvin>(data.CellTemperaureMaximum).GetValue();
        message0.Data = v;
        
        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message0)));

        Message message1;
        message1.Id = MessageId::CellVoltMinId;
        CellId c1;
        std::memset(c1.Name, 0, sizeof(c1.Name));
        data.CellVoltageMinimumName.copy(c1.Name, std::min(sizeof(c1.Name), data.CellVoltageMinimumName.size()));
        message1.Data = c1;
        result.push_back(std::make_shared<Message>(std::move(message1)));

        Message message2;
        message2.Id = MessageId::CellVoltMaxId;
        CellId c2;
        std::memset(c2.Name, 0, sizeof(c2.Name));
        data.CellVoltageMaximumName.copy(c2.Name, std::min(sizeof(c2.Name), data.CellVoltageMaximumName.size()));
        message2.Data = c2;
        result.push_back(std::make_shared<Message>(std::move(message2)));

        Message message3;
        message3.Id = MessageId::CellTempMinId;
        CellId c3;
        std::memset(c3.Name, 0, sizeof(c3.Name));
        data.CellTemperaureMinimumName.copy(c3.Name, std::min(sizeof(c3.Name), data.CellTemperaureMinimumName.size()));
        message3.Data = c3;
        result.push_back(std::make_shared<Message>(std::move(message3)));

        Message message4;
        message4.Id = MessageId::CellTempMaxId;
        CellId c4;
        std::memset(c4.Name, 0, sizeof(c4.Name));
        data.CellTemperaureMaximumName.copy(c4.Name, std::min(sizeof(c4.Name), data.CellTemperaureMaximumName.size()));
        message4.Data = c4;
        result.push_back(std::make_shared<Message>(std::move(message4)));

        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateBatteryStats(Victron::BatteryStats& data)
    {
        Message message;

        message.Id = MessageId::BatteryStats;
        
        BatteryStats v;
        v.VoltageCentiVolt = data.Voltage.Value.ScaleTo(Units::Scale::Centi, true);
        v.CurrentDeciAmpere = data.Current.Value.ScaleTo(Units::Scale::Deci, true);
        Units::Unit temp { data.Temperature.GetValue() };
        v.TemperatureDeciCelsius = temp.Value.ScaleTo(Units::Scale::Deci, true);
        message.Data = v;
        
        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateManufacturerInfo()
    {
        Message message;

        message.Id = MessageId::ManufacturerInfo;

        ManufacturerInfo v;
        for ( auto c = 0; c < sizeof(v.Name); c++ )
        {
            v.Name[c] = '\0';
        }
        for ( auto c = 0; 0 != ManufacturerName[c]; c++ )
        {
            v.Name[c] = ManufacturerName[c];
        }
        message.Data = v;

        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }

    std::vector<std::shared_ptr<Message>> Message::Factory::CreateProductInfo()
    {
        Message message;

        message.Id = MessageId::ProductInfo;
        
        ProductInfo v;
        for ( auto c = 0; c < sizeof(v.Name); c++ )
        {
            v.Name[c] = '\0';
        }
        for ( auto c = 0; 0 != ProductName[c]; c++ )
        {
            v.Name[c] = ProductName[c];
        }
        message.Data = v;

        std::vector<std::shared_ptr<Message>> result;
        result.push_back(std::make_shared<Message>(std::move(message)));
        return result;
    }
}
