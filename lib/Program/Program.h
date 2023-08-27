/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#pragma once

#include <memory>

#include <../Gpio/Pin.h>
#include <../CanTwai/Can.h>
#include <../CanTwai/Configuration.h>
#include <../MorseCode/Generator.h>
#include <../MorseCode/Configuration.h>

namespace Program
{
    /// @brief GPIO wired to the LED. Depends on the actual board used or wiring.
    #define LED_BUILTIN GPIO_NUM_2
    // #define LED_BUILTIN GPIO_NUM_13
    // #define LED_BUILTIN GPIO_NUM_4

    /// @brief Timeout in milliseconds to wait for a CAN message to be sent.
    constexpr uint32_t waitTimeoutMs = 950;

    /// @brief Represents the main program.
    class Program
    {
        private:
            /// @brief A thread function.
            /// @param pvParameter The parameter passed to the thread function.
            static void OutputFunc(void *pvParameter);
            
            /// @brief The CAN bus configuration instance.
            std::shared_ptr<CanTwai::Configuration> twaiConfiguration;
            
            /// @brief The CAN bus instance.
            std::shared_ptr<CanTwai::Can> twai;

            /// @brief The GPIO LED pin instance.
            std::shared_ptr<Gpio::Pin> pin;

            /// @brief A morse code generator configuration instance.
            std::shared_ptr<MorseCode::Configuration> generatorConfiguration;

            /// @brief A morse code generator instance.
            std::shared_ptr<MorseCode::Generator> generator;

            /// @brief The message to send.
            std::string message = "Hello, world!";
            
            /// @brief Default .ctor. Only to be used by the Factory.
            explicit Program();

            /// @brief Needed by Factory for class instantiation.
            friend std::unique_ptr<Program> std::make_unique<Program>();

        public:
            /// @brief Move .ctor.
            /// @param other Existing instance to move from. 
            Program(Program&& other) noexcept;

            /// @brief Copy .ctor. Not supported. 
            /// @param other Existing instance to copy from. 
            Program(const Program& other) = delete;

            /// @brief Move assignment. Not supported.
            /// @param other Existing instance to move from.
            /// @return Reference to this instance.
            Program& operator=(const Program& other) = delete;

            /// @brief Invoke the main program task.
            virtual void Invoke();
        
        /// @brief Factory class for the Program class.
        class Factory
        {
            private:
                /// @brief Default .ctor. Not supported.
                Factory() = delete;

            public:
                /// @brief Creates an instance of the Program class.
                /// @return An instance to the Program class. 
                static std::unique_ptr<Program> Create();

        };
    };
}

#endif
