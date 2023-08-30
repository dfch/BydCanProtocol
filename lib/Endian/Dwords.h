/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include "Dword.h"

namespace Endian
{
    #pragma pack(push, 1)
    struct tagDwords
    {
        Dword Dword0;
        Dword Dword1;
    };
    #pragma pack(pop)

    using Dwords = tagDwords;
}
