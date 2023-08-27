/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#include "Program.h"

#include <../Contract/Contract.h>
#include <../Threading/Thread.h>
#include <../Gpio/Pin.h>
#include <../CanTwai/Can.h>
#include <../CanTwai/Configuration.h>
#include <../MorseCode/Generator.h>
#include <../MorseCode/Configuration.h>

namespace Program
{
    Program::Program()
    {
        pin = std::make_shared<Gpio::Pin>(LED_BUILTIN, GPIO_MODE_OUTPUT);

        generatorConfiguration = std::make_shared<MorseCode::Configuration>();
        generatorConfiguration->Transmit = [this](int ms)
        {
            this->pin->Set(true);
            Threading::Thread::Sleep(ms);
            this->pin->Set(false);
        };
        generatorConfiguration->NoTransmit = [this](int ms)
        { 
            this->pin->Set(false);
            Threading::Thread::Sleep(ms);
        };
        generator = std::make_shared<MorseCode::Generator>(generatorConfiguration);

        std::string sequence = "";
        sequence = "sA";
        generator->Send(sequence);

        this->twaiConfiguration = std::make_shared<CanTwai::Configuration>(GPIO_NUM_1, GPIO_NUM_3, TWAI_MODE_NORMAL, 500);
        twai = CanTwai::Can::Factory::Create(this->twaiConfiguration);
    }

    void Program::OutputFunc(void *pvParameters)
    {
        Contract::Requires([pvParameters] { return nullptr != pvParameters; }, NAMEOF(pvParameters));
        
        auto instance = (Program*) pvParameters;

        while(true)
        {
            instance->generator->Send(instance->message);
        }
    }

    Program::Program(Program &&other) noexcept
    {
        twaiConfiguration = std::move(other.twaiConfiguration);
        other.twaiConfiguration = nullptr;

        twai = std::move(other.twai);
        other.twai = nullptr;

        pin = std::move(other.pin);
        other.pin = nullptr;

        generator = std::move(other.generator);
        other.generator = nullptr;

        generatorConfiguration = std::move(other.generatorConfiguration);
        other.generatorConfiguration = nullptr;
    }

    void Program::Invoke()
    {
        while(true)
        {
            auto result = twai->EmulateByd();
            Contract::Requires([result] { return result; });

            Threading::Thread::Sleep(waitTimeoutMs);
        }
    }
}

#endif
