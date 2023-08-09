/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <variant>
#include <memory>
#include <vector>

#include "Constants.h"
#include "Messages/MessageId.h"
#include "Messages/Raw.h"
#include "Messages/Dvcc.h"
#include "Messages/StateInfo.h"
#include "Messages/Alarms.h"
#include "Messages/BatteryStats.h"
#include "Messages/BatteryInfo.h"
#include "Messages/BankInfo.h"
#include "Messages/CellInfo.h"
#include "Messages/CellId.h"
#include "Messages/History.h"
#include "Messages/BatterySize.h"
#include "Messages/ManufacturerInfo.h"
#include "Messages/ProductInfo.h"

#include <../Victron/Dvcc.h>
#include <../Victron/StateInfo.h>
#include <../Victron/BankInfo.h>
#include <../Victron/CellInfo.h>
#include <../Victron/BatteryStats.h>
#include <../Victron/AlarmWarning.h>

namespace Byd
{
    /// @brief Represents a BYD CAN message.
    class Message
    {
        private:
            /// @brief Default .ctor. Only used by the factory.
            Message();

        public:
            /// @brief Represents the CAN message id.
            MessageId Id;

            /// @brief Represents the data of the CAN message.
            std::variant
            <
                Raw,
                Dvcc, 
                StateInfo, 
                Alarms, 
                BatteryStats, 
                BatteryInfo, 
                BankInfo, 
                CellInfo, 
                CellId, 
                History, 
                BatterySize, 
                ManufacturerInfo, 
                ProductInfo
            > Data;

            /// @brief Serialises the data of the message into a byte array.
            Raw SerialiseData();

            /// @brief Represents a factory for creating CAN messages.
            class Factory
            {
                private:
                    /// @brief Default .ctor. Not supported.
                    Factory() = delete;

                public:
                    /// @brief Creates an empty CAN message (without id or data).
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> Create();

                    /// @brief Creates a CAN message with id #Byd::MessageId::Dvcc. 
                    /// @param data Contains DVCC Voltage and Ampere information.
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateDvcc(Victron::Dvcc& data);
                    
                    /// @brief Creates a CAN message with id #Byd::MessageId::StateInfo
                    /// @param data Contains SoC, SoH, total and Availale battery size.
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateStateInfo(Victron::StateInfo& data);
                    
                    /// @brief Creates a CAN message with id #Byd::MessageId::AlarmsWarnings
                    /// @param data The bit mask for all current active alarms and warnings.
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateAlarmWarning(Victron::AlarmWarning& data);
                    
                    /// @brief Creates a CAN message with id #Byd::MessageId::EventsUnused
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateEventsUnused();
                    
                    /// @brief Creates a CAN message with id #Byd::MessageId::BatteryStats
                    /// @param data 
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateBatteryStats(Victron::BatteryStats& data);
                    
                    /// @brief Creates a CAN message with id #Byd::MessageId::BatteryInfo
                    /// @param data Contains SoC, SoH, total and Availale battery size.
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateBatteryInfo(Victron::StateInfo& data);
                    
                    /// @brief Creates a CAN message with id #Byd::MessageId::Unknown0
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateUnknown0();
                    
                    /// @brief Creates a CAN message with id #Byd::MessageId::BankInfo
                    /// @param data Contains the total number of batteries and the number of batteries that are currently offline.
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateBankInfo(Victron::BankInfo& data);
                    
                    /// @brief Creates CAN messages with cell information id #Byd::MessageId::CellInfo
                    /// @param data Contains information about lowest/highest cell voltage/temperature and their cell names.
                    /// @return Returns a vector with these messages: #Byd::MessageId::CellInfo, #Byd::MessageId::CellVoltMinId, #Byd::MessageId::CellVoltMaxId, #Byd::MessageId::CellTempMinId, #Byd::MessageId::CellTempMaxId.
                    static std::vector<std::shared_ptr<Message>> CreateCellInfo(Victron::CellInfo& data);
                    
                    /// @brief Creates a CAN message with id #Byd::MessageId::History
                    /// @param data Contains counter for charged and discharged energy.
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateHistory(Victron::BatteryStats& data);
                    
                    /// @brief Creates a CAN message with id #Byd::MessageId::BatterySize
                    /// @param data Contains SoC, SoH, total and Availale battery size.
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateBatterySize(Victron::StateInfo& data);

                    /// @brief Creates a CAN message with id #Byd::MessageId::ManufacturerInfo
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateManufacturerInfo();
                    
                    /// @brief Creates a CAN message with id #Byd::MessageId::ProductInfo
                    /// @return Returns a vector with a single CAN message.
                    static std::vector<std::shared_ptr<Message>> CreateProductInfo();

            };
    };
}
