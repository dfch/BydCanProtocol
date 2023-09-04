// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#if defined(ESP_PLATFORM)

#include "Program.h"

namespace Program
{
    std::unique_ptr<Program> Program::Factory::Create()
    {
        auto result = std::make_unique<Program>();

        return result;
    }
}

#endif
