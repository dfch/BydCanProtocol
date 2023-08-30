/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include "Rs485.h"

#include <cstddef>
#include <span>

#include <Contract.h>

using namespace JkBms;

namespace JkBms
{
    Rs485::Rs485(std::vector<std::uint8_t> &data)
    {
        this->data = data;
    }

    Rs485::Rs485(std::uint8_t *data, size_t length)
    {
        Contract::Expects([data] { return nullptr != data; });

        this->data = std::vector<std::uint8_t>(data, data + length);
    }

    std::uint8_t Rs485::operator[] (std::size_t index)
    {
        Contract::Expects([this, index] { return index < this->data.size(); }, Contract::ErrorCode::OutOfRange);

        auto result = this->data[index];

        return result;
    }

    ValidationResult Rs485::IsValid() const noexcept
    {
        Frame frame;

        const auto frameSize = data.size();

        // Check minimum frame size.
        if(FrameSizeMinimum >= frameSize) return ValidationResult::FrameTooShort;

        // Map data to header of frame.
        frame.Header = reinterpret_cast<const Header*>(data.data());
        if(!frame.Header->StartOfFrame.IsValid()) return ValidationResult::InvalidHeader;

        // Check if length specified in header matches the frame size.
        if(frame.Header->GetFrameLength() != frameSize) return ValidationResult::InvalidLength;
        
        // Calculate size of body.
        const auto bodySize = frameSize - FrameSizeMinimum;

        // Map data to body of frame.
        frame.Body = reinterpret_cast<const InformationUnit*>(data.data() + sizeof(Header));
        if(!frame.Body->Identifier.IsValid()) return ValidationResult::InvalidIdentifier;

        // Map data to footer of frame.
        frame.Footer = reinterpret_cast<const Footer*>(data.data() + sizeof(Header) + bodySize);
        if(!frame.Footer->EndCode.IsValid()) return ValidationResult::InvalidEndCode;

        // Calculate checksum.
        if(!frame.IsValidChecksum()) return ValidationResult::InvalidChecksum;

        return ValidationResult::Success;
    }
}
