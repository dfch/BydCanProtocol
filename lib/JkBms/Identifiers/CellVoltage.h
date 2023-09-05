// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <cstddef>

#include <Contract.h>
#include <Byte.h>
#include <Word.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;

    #pragma pack(push, 1)
    /// @brief Battery voltage information. Each cell is represented by a CellInfo.
    struct tagCellVoltage
    {
        /// @brief BMS settings identifier.
        Identifier Identifier;

        /// @brief Number of bytes of the following data.
        uint8_t Length;

        /// @brief Voltage information for a single cell.
        struct tagCellInfo
        {
            /// @brief Number of the cell.
            Byte Number;
            /// @brief Voltage of the cell in milli volt. Big endian.
            Word MilliVolt;
        } CellInfos[]; // Cell information.
        
        /// @brief Returns the number of cells.
        const size_t CellCount() const noexcept 
        {
            Contract::Expects([this] { return 0 == this->Length % sizeof(tagCellInfo); }, NAMEOF(CellVoltage::CellCount) " Invalid value: Length");

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
    };
    #pragma pack(pop)

    using CellVoltage = tagCellVoltage;
}
