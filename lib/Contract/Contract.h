// Copyright (c) Bjarne Stroustrup
// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <stdexcept>
#include <cstdint>
#include <iostream>
#include <vector>
#include <source_location>

#include "EscalationPolicy.h"
#include "ErrorCode.h"

namespace Contract
{
    #define NAMEOF(name) #name

    /// @brief Maximum message length.
    constexpr uint16_t MessageLength = 256;

    /// @brief Default escalation policy for handling a failed assertion.
    constexpr EscalationPolicy DefaultEscalationPolicy = EscalationPolicy::Throw;

    /// @brief Checks for a pre-ondition; if the condition is false, follows the DefaultEscalationPolicy.
    /// @tparam C The conditional expression to test.
    /// @tparam policy The escalation policy to follow if the condition is false.
    /// @param condition The conditional expression to test.
    /// @param errorCode The error code to be used when following the escalation policy.
    template<EscalationPolicy policy = DefaultEscalationPolicy, class C>
    constexpr void Expects(C condition, ErrorCode errorCode = ErrorCode::InvalidArgument, const std::source_location& location = std::source_location::current())
    {
        if constexpr(EscalationPolicy::Throw == policy)
        {
            if(!condition()) 
            {
                std::vector<char> message(MessageLength);
                const char* format = "Expectation failed: 0x%04X\n";

                std::snprintf(message.data(), message.size(), format, errorCode);

                throw std::invalid_argument(message.data());
            }
        }

        if constexpr(EscalationPolicy::Log == policy)
        {
            if(!condition()) 
            {
                std::cerr << 
                    location.file_name() <<
                    ":" <<
                    std::to_string(location.line()) <<
                    ":" <<
                    "Expectation failed: " << 
                    uint16_t(errorCode) << 
                    " [0x" <<
                    std::hex <<
                    uint16_t(errorCode) << 
                    "]\n";
            }
        }

        if constexpr(EscalationPolicy::Abort == policy)
        {
            if(!condition()) 
            {
                abort();
            }
        }
    }

    /// @brief Checks for a pre-condition; if the condition is false, follows the DefaultEscalationPolicy.
    /// @tparam C The conditional expression to test.
    /// @tparam policy The escalation policy to follow if the condition is false.
    /// @param condition The conditional expression to test.
    /// @param customMessage The error message to be used when following the escalation policy.
    template<EscalationPolicy policy = DefaultEscalationPolicy, class C>
    constexpr void Expects(C condition, const char* customMessage, const std::source_location& location = std::source_location::current())
    {
        if constexpr(EscalationPolicy::Throw == policy)
        {
            if(!condition()) 
            {
                std::vector<char> message(MessageLength);
                const char* format = "%s:%d:Expectation failed: %s\n";
                const char* messageDefault = "Expectation failed (custom message too long).";

                auto size = std::snprintf(message.data(), message.size(), format, location.file_name(), location.line(), customMessage);
                throw std::invalid_argument(0 < size ? message.data() : messageDefault);
            }
        }

        if constexpr(EscalationPolicy::Log == policy)
        {
            if(!condition()) 
            {
                std::cerr << 
                    location.file_name() <<
                    ":" <<
                    std::to_string(location.line()) <<
                    ":" <<
                    "Expectation failed: " << 
                    customMessage << 
                    "\n";
            }
        }

        if constexpr(EscalationPolicy::Abort == policy)
        {
            if(!condition()) 
            {
                abort();
            }
        }
    }

    /// @brief Checks for a post-condition; if the condition is false, follows the DefaultEscalationPolicy.
    /// @tparam C The conditional expression to test.
    /// @tparam policy The escalation policy to follow if the condition is false.
    /// @param condition The conditional expression to test.
    /// @param errorCode The error code to be used when following the escalation policy.
    template<EscalationPolicy policy = DefaultEscalationPolicy, class C>
    constexpr void Ensures(C condition, ErrorCode errorCode = ErrorCode::InvalidArgument, const std::source_location& location = std::source_location::current())
    {
        if constexpr(EscalationPolicy::Throw == policy)
        {
            if(!condition()) 
            {
                std::vector<char> message(MessageLength);
                const char* format = "Post-condition failed: 0x%04X\n";

                std::snprintf(message.data(), message.size(), format, errorCode);

                throw std::invalid_argument(message.data());
            }
        }

        if constexpr(EscalationPolicy::Log == policy)
        {
            if(!condition()) 
            {
                std::cerr << 
                    location.file_name() <<
                    ":" <<
                    std::to_string(location.line()) <<
                    ":" <<
                    "Post-condition failed: " << 
                    uint16_t(errorCode) << 
                    " [0x" <<
                    std::hex <<
                    uint16_t(errorCode) << 
                    "]\n";
            }
        }

        if constexpr(EscalationPolicy::Abort == policy)
        {
            if(!condition()) 
            {
                abort();
            }
        }
    }

    /// @brief Checks for a post-condition; if the condition is false, follows the DefaultEscalationPolicy.
    /// @tparam C The conditional expression to test.
    /// @tparam policy The escalation policy to follow if the condition is false.
    /// @param condition The conditional expression to test.
    /// @param customMessage The error message to be used when following the escalation policy.
    template<EscalationPolicy policy = DefaultEscalationPolicy, class C>
    constexpr void Ensures(C condition, const char* customMessage, const std::source_location& location = std::source_location::current())
    {
        if constexpr(EscalationPolicy::Throw == policy)
        {
            if(!condition()) 
            {
                std::vector<char> message(MessageLength);
                const char* format = "%s:%d:Post-condition failed: %s\n";
                const char* messageDefault = "Post-condition failed (custom message too long).";

                auto size = std::snprintf(message.data(), message.size(), format, location.file_name(), location.line(), customMessage);
                throw std::invalid_argument(0 < size ? message.data() : messageDefault);
            }
        }

        if constexpr(EscalationPolicy::Log == policy)
        {
            if(!condition()) 
            {
                std::cerr << 
                    location.file_name() <<
                    ":" <<
                    std::to_string(location.line()) <<
                    ":" <<
                    "Post-condition failed: " << 
                    customMessage << 
                    "\n";
            }
        }

        if constexpr(EscalationPolicy::Abort == policy)
        {
            if(!condition()) 
            {
                abort();
            }
        }
    }

    /// @brief Checks for a condition; if the condition is false, follows the DefaultEscalationPolicy.
    /// @tparam C The conditional expression to test.
    /// @tparam policy The escalation policy to follow if the condition is false.
    /// @param condition The conditional expression to test.
    /// @param errorCode The error code to be used when following the escalation policy.
    template<EscalationPolicy policy = DefaultEscalationPolicy, class C>
    constexpr void Assert(C condition, ErrorCode errorCode = ErrorCode::InvalidArgument, const std::source_location& location = std::source_location::current())
    {
        if constexpr(EscalationPolicy::Throw == policy)
        {
            if(!condition()) 
            {
                std::vector<char> message(MessageLength);
                const char* format = "Assertion failed: 0x%04X\n";

                std::snprintf(message.data(), message.size(), format, errorCode);

                throw std::invalid_argument(message.data());
            }
        }

        if constexpr(EscalationPolicy::Log == policy)
        {
            if(!condition()) 
            {
                std::cerr << 
                    location.file_name() <<
                    ":" <<
                    std::to_string(location.line()) <<
                    ":" <<
                    "Assertion failed: " << 
                    uint16_t(errorCode) << 
                    " [0x" <<
                    std::hex <<
                    uint16_t(errorCode) << 
                    "]\n";
            }
        }

        if constexpr(EscalationPolicy::Abort == policy)
        {
            if(!condition()) 
            {
                abort();
            }
        }
    }

    /// @brief Checks for a condition; if the condition is false, follows the DefaultEscalationPolicy.
    /// @tparam C The conditional expression to test.
    /// @tparam policy The escalation policy to follow if the condition is false.
    /// @param condition The conditional expression to test.
    /// @param customMessage The error message to be used when following the escalation policy.
    template<EscalationPolicy policy = DefaultEscalationPolicy, class C>
    constexpr void Assert(C condition, const char* customMessage, const std::source_location& location = std::source_location::current())
    {
        if constexpr(EscalationPolicy::Throw == policy)
        {
            if(!condition()) 
            {
                std::vector<char> message(MessageLength);
                const char* format = "%s:%d:Assertion failed: %s\n";
                const char* messageDefault = "Assertion failed (custom message too long).";

                auto size = std::snprintf(message.data(), message.size(), format, location.file_name(), location.line(), customMessage);
                throw std::invalid_argument(0 < size ? message.data() : messageDefault);
            }
        }

        if constexpr(EscalationPolicy::Log == policy)
        {
            if(!condition()) 
            {
                std::cerr << 
                    location.file_name() <<
                    ":" <<
                    std::to_string(location.line()) <<
                    ":" <<
                    "Assertion failed: " << 
                    customMessage << 
                    "\n";
            }
        }

        if constexpr(EscalationPolicy::Abort == policy)
        {
            if(!condition()) 
            {
                abort();
            }
        }
    }
}
