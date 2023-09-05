// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <cstddef>

#include <Contract.h>
#include <Dword.h>

#include "Header.h"
#include "InformationUnit.h"
#include "Footer.h"

namespace JkBms
{
    constexpr size_t FrameSizeMinimum = 
        sizeof(Header) +
        sizeof(Footer);

    #pragma pack(push, 1)
    /// @brief Represents a complete frame to be sent or received by either communication partner.
    struct tagFrame
    {
        const Header* Header;
        const InformationUnit* Body;
        const Footer* Footer;

        /// @brief Calculates the checksum of the frame.
        /// The complete (Header, Body, Footer) frame must be initialised prior ot calling this function.
        {
            Contract::Expects([this] 
            {
                return nullptr != this->Header && nullptr != this->Footer;
            }, NAMEOF(CalculateChecksum));

            uint32_t result { 0 };

            auto data = reinterpret_cast<const uint8_t*>(this->Header);

            for(size_t c = 0; c < Header->GetFrameLength() - sizeof(Footer->Checksum); ++c)
            {
                result += data[c];
            }

            return result;
        };

        /// @brief Determines whether the checksum of the frame is valid or not.
        /// @return Return true, if the checksum is valid; false, otherwise.
        bool IsValidChecksum() const noexcept
        {
            if(nullptr == Header || nullptr == Body || nullptr == Footer ) return false;

            auto calc = CalculateChecksum();
            auto stor = this->Footer->Checksum.ToLittleEndian();
            auto result = calc == stor;
            
            if(!result) fprintf(stderr, "CrcStor (%08X) != CrcCalc (%08X)\n", stor, calc);
            
            return result;
        }
    };
    #pragma pack(pop)
    
    using Frame = tagFrame;
}
