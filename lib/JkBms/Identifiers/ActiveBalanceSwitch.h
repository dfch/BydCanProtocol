// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Byte.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;

    #pragma pack(push, 1)
    /// @brief Represents the Active Balance Switch (0,1) of the BMS.
    struct tagActiveBalanceSwitch
    {
        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief Flag. 1, Active Balance Switch is set; 0, otherwise.
        Byte Value;

        bool IsSet()
        {
            return Value.Value;
        }

        void Set(bool flag)
        {
            Value.Value = flag;
        }
    };
    #pragma pack(pop)

    /// @brief Represents the Active Balance Switch (0,1) of the BMS.
    using ActiveBalanceSwitch = tagActiveBalanceSwitch;
}
