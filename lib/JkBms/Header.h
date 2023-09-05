// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <cstddef>

#include <Word.h>
#include "ValidationResult.h"
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

        /// @brief Validates the header and returns a ValidationResult.
        /// @return Success, if the header validated without errors. Otherwise, errors have been detected.
        ValidationResult GetValidationResult() const noexcept
        {
            if(!StartOfFrame.IsValid()) return ValidationResult::InvalidStartOfFrame;

            if(CommandWord != CommandWord::Activate &&
                CommandWord != CommandWord::Write && 
                CommandWord != CommandWord::Read && 
                CommandWord != CommandWord::Password && 
                CommandWord != CommandWord::ReadAll) return ValidationResult::InvalidCommandWord;
            
            if(FrameSource != FrameSource::Bms && 
                FrameSource != FrameSource::Bluetooth && 
                FrameSource != FrameSource::Gps && 
                FrameSource != FrameSource::Terminal) return ValidationResult::InvalidFrameSource;
            
            if(TransmissionType != TransmissionType::RequestFrame && 
                TransmissionType != TransmissionType::ResponseFrame && 
                TransmissionType != TransmissionType::ReportFrame) return ValidationResult::InvalidTransmissionType;
        }

        /// @brief Determines whether the header is valid. 
        /// @return True, if the header is valid; false, otherwise.
        bool IsValid() const noexcept
        {
            return ValidationResult::Success == GetValidationResult();
        }
    };
    #pragma pack(pop)

    using Header = tagHeader;
}
