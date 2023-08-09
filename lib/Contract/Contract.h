/**
* Copyright (c) Bjarne Stroustrup
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <stdexcept>
#include <cstdint>
#include <iostream>
#include <vector>

#include "EscalationPolicy.h"
#include "ErrorCode.h"

namespace Contract
{
    #define NAMEOF(name) #name

    /// @brief Maximum message length.
    constexpr uint16_t MessageLength = 256;

    /// @brief Default escalation policy for handling a failed assertion.
    constexpr EscalationPolicy DefaultEscalationPolicy = EscalationPolicy::Throw;

    /// @brief Checks for a condition; if the condition is false, follows the DefaultEscalationPolicy.
    /// @tparam C The conditional expression to test.
    /// @tparam policy The escalation policy to follow if the condition is false.
    /// @param condition The conditional expression to test.
    /// @param errorCode The error code to be used when following the escalation policy.
    template<EscalationPolicy policy = DefaultEscalationPolicy, class C>
    constexpr void Requires(C condition, ErrorCode errorCode = ErrorCode::InvalidArgument)
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
    constexpr void Requires(C condition, const char* customMessage)
    {
        if constexpr(EscalationPolicy::Throw == policy)
        {
            if(!condition()) 
            {
                std::vector<char> message(MessageLength);
                const char* format = "Assertion failed: %s\n";
                const char* messageDefault = "Assertion failed (custom message too long).";

                auto size = std::snprintf(message.data(), message.size(), format, customMessage);
                throw std::invalid_argument(0 < size ? message.data() : messageDefault);
            }
        }

        if constexpr(EscalationPolicy::Log == policy)
        {
            if(!condition()) 
            {
                std::cerr << 
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
