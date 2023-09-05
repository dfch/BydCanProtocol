// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Dword.h>
#include <AmpereHour.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;
    using namespace Units;

    #pragma pack(push, 1)
    /// @brief Represents the Total Battery Cycle Capacity in AmpereHour of the BMS.
    struct tagTotalBatteryCycleCapacity
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded AmpereHour.
        Dword Value;

        /// @brief Converts the underlying value to AmpereHour. 
        /// @return The converted AmpereHour.
        AmpereHour ToAmpereHour() const 
        {
            AmpereHour result(Value.ToLittleEndian());

            return result;
        }

        /// @brief Sets an AmpereHour to the underlying value.
        /// @param value The value to set.
        void FromAmpereHour(AmpereHour value)
        {
            auto ah = value.Value.GetValue();
            Contract::Expects([ah] { return 0 <= ah; });

            Value.Value = ah;
        }
    };
    #pragma pack(pop)

    /// @brief Represents the Total Battery Cycle Capacity in AmpereHour of the BMS.
    using TotalBatteryCycleCapacity = tagTotalBatteryCycleCapacity;
}
