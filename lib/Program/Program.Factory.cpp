/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

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
