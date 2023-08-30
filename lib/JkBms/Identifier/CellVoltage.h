/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>
#include <cstddef>

#include <Contract.h>
#include <Byte.h>
#include <Word.h>

#include "Identifier.h"

namespace JkBms
{
    using namespace Endian;

    #pragma pack(push, 1)
    /// @brief Battery voltage information. Each cell is represented by a CellInfo.
    struct tagCellVoltage
    {
        Identifier Identifier;

        uint8_t Length; // Number of bytes of the following data.

        struct tagCellInfo
        {
            Byte Number; // Number of the cell.
            Word MilliVolt; // Voltage of the cell in milli volt. Big endian.
        } CellInfos[]; // Cell information.
        
        /// @brief Returns the number of cells.
        const size_t CellCount() const noexcept 
        {
            Contract::Expects([this] { return 0 == this->Length % sizeof(tagCellInfo); }, "Invalid value: Length");

            return Length / sizeof(tagCellInfo); 
        }

        /// @brief Returns the average voltage of all cells in milli volt.
        const uint16_t GetAverageVoltageMilliVolt() const noexcept
        {
            uint16_t result = 0;
            auto count = CellCount();

            for(auto c = 0; c < count; ++c)
            {
                result += CellInfos[c].MilliVolt.ToLittleEndian();
            }

            return result / count;
        }

        /// @brief The functor to be used for processing this identifier.
        // void operator()() const noexcept
        // {
        //     return;
        // }
    };
    #pragma pack(pop)

    using CellVoltage = tagCellVoltage;
}
