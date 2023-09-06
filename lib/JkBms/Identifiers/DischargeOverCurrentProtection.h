// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "Identifier.h"
#include "AmpereBase.h"

namespace JkBms::Identifiers
{
    #pragma pack(push, 1)
    /// @brief Represents the Discharge Over Current Protection (A) of the BMS.
    struct tagDischargeOverCurrentProtection : AmpereBase
    {
        // Intentionally left blank
    };
    #pragma pack(pop)

    /// @brief Represents the Discharge Over Current Protection (A) of the BMS.
    using DischargeOverCurrentProtection = tagDischargeOverCurrentProtection;
}
