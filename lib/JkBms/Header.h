// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <cstddef>

#include <Word.h>
#include "StartOfFrame.h"
#include "BmsTerminalNumber.h"
#include "CommandWord.h"
#include "FrameSource.h"
#include "TransmissionType.h"

namespace JkBms
{
    using namespace Endian;

    #pragma pack(push, 1)
    /// @brief The fixed-size start part of the frame.
    struct tagHeader
    {
        StartOfFrame StartOfFrame;

        Word Length; // The total length in bytes of the frame excluding StartOfFrame.

        BmsTerminalNumber BmsTerminalNumber;

        CommandWord CommandWord;

        FrameSource FrameSource;

        TransmissionType TransmissionType;

        /// @brief Gets the total length in bytes of the frame as specified in the header (including the start of frame field).
        /// @return The total length in bytes of the frame. Or 0 if the length could not be determined.
        size_t GetFrameLength() const noexcept 
        {
            try
            {
                return Length.ToLittleEndian() + sizeof(StartOfFrame); 
            }
            catch(...)
            {
                return 0;
            }
        }
    };
    #pragma pack(pop)

    using Header = tagHeader;
}
