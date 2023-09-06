// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Word.h>
#include <Ampere.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;
    using namespace Units;

    #pragma pack(push, 1)
    /// @brief Represents the current (A) of the BMS.
    struct tagAmpereBase
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded Ampere.
        Word Value;

        /// @brief Converts the underlying value to Ampere. 
        /// @return The converted Ampere.
        Ampere ToAmpere() const 
        {
            Ampere result(Value.ToLittleEndian());

            return result;
        }

        /// @brief Sets the underlying value.
        /// @param value The value to set.
        void FromAmpere(Ampere value)
        {
            Value.Value = value.Value.GetValue();
        }
    };
    #pragma pack(pop)

    /// @brief Represents the current (A) of the BMS.
    using AmpereBase = tagAmpereBase;

    /// @brief Represents the Discharge Over Current Protection (A) of the BMS.
    struct tagDischargeOverCurrentProtection : AmpereBase
    {
        // Intentionally left blank
    };

    /// @brief Represents the Discharge Over Current Protection (A) of the BMS.
    using DischargeOverCurrentProtection = tagDischargeOverCurrentProtection;
}
