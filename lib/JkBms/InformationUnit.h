/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

#include "Identifier.h"

#include "Identifier/CellVoltage.h"

namespace JkBms
{
    #pragma pack(push, 1)
    struct tagInformationUnit
    {
        Identifier Identifier;
        uint8_t* Data;
    };
    #pragma pack(pop)

    using InformationUnit = tagInformationUnit;
}
