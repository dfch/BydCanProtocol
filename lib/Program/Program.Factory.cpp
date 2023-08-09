/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#include "Program.h"

namespace Program
{
    std::shared_ptr<Program> Program::Factory::Create()
    {
        Program instance;
        
        return std::make_shared<Program>(std::move(instance));
    }
}

#endif
