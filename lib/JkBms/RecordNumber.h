/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

#include <Word.h>

namespace JkBms
{
    using namespace Endian;

    #pragma pack(push, 1)
    /// @brief Represents the record number.
    struct tagRecordNumber
    {
        Word CodeWordLow;
        uint8_t CodeByteHigh;
        uint8_t Random; // Meaningless, random data.
    };
    #pragma pack(pop)
    
    using RecordNumber = tagRecordNumber;
}
