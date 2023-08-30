/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>
#include <cstddef>

#include <Dword.h>

#include "RecordNumber.h"
#include "EndCode.h"

namespace JkBms
{
    using namespace Endian;

    #pragma pack(push, 1)
    /// @brief The fixed-size end part of the frame.
    struct tagFooter
    {
        RecordNumber RecordNumber;

        EndCode EndCode;

        Dword Checksum;
    };
    #pragma pack(pop)
    
    using Footer = tagFooter;
}
