// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>

namespace JkBms
{
    /// @brief Defines the type of command to send, such as reading or writing BMS.
    enum class CommandWord : uint8_t
    {
        Activate = 0x01, // When the BMS is sleeping, the control terminal must send activation command to communicate with the BMS. Do other operations after replying.
        Write = 0x02, // Configure BMS parameter instructions.
        Read = 0x03, // Read BMS identification code data.
        Password = 0x05, // When you want to modify the parameters, you can modify the parameters only after t [TODO text missing].
        ReadAll = 0x06, // Read all the data of the identification code table at one time.
    };
}
