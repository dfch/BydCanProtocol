/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include "Rs485.h"

#include <cstddef>

#include <Contract.h>

#include "Frame.h"

using namespace JkBms;

namespace JkBms
{
    using std::unique_ptr;
    using std::vector;
    using std::uint8_t;

    Rs485::Rs485(vector<uint8_t>& data)
        : Rs485(std::make_unique<std::vector<uint8_t>>(std::move(data))) { }

    Rs485::Rs485(unique_ptr<vector<uint8_t>> data)
        : ptr(std::move(data)), frame(ValidationResult::NotParsed)
    { 
        ParseData();
    }

    uint8_t Rs485::operator[](size_t index)
    {
        Contract::Expects([this, index] { return index < this->ptr.get()->size(); }, Contract::ErrorCode::OutOfRange);

        auto result = ptr.get()->data()[index];

        return result;
    }

    void Rs485::ParseData() noexcept
    {
        frame = ValidationResult::NotParsed;

        const auto data = ptr.get();

        const auto frameSize = data->size();

        // Check minimum frame size.
        if(FrameSizeMinimum >= frameSize) 
        {
            frame = ValidationResult::FrameTooShort;
            return;
        }

        // Map data to header of frame.
        (*frame).Header = reinterpret_cast<const Header*>(data->data());
        if(!(*frame).Header->StartOfFrame.IsValid()) 
        {
            frame = ValidationResult::InvalidHeader;
            return;
        }

        // Check if length specified in header matches the frame size.
        if((*frame).Header->GetFrameLength() != frameSize) 
        {
            frame = ValidationResult::InvalidLength;
            return;
        }
        
        // Calculate size of body.
        const auto bodySize = frameSize - FrameSizeMinimum;

        // Map data to body of frame.
        (*frame).Body = reinterpret_cast<const InformationUnit*>(data->data() + sizeof(Header));
        if(!(*frame).Body->Identifier.IsValid()) 
        {
            frame = ValidationResult::InvalidIdentifier;
            return;
        }

        // Map data to footer of frame.
        (*frame).Footer = reinterpret_cast<const Footer*>(data->data() + sizeof(Header) + bodySize);
        if(!(*frame).Footer->EndCode.IsValid())
        {
            frame = ValidationResult::InvalidEndCode;
            return;
        }

        // Calculate checksum.
        if(!(*frame).IsValidChecksum()) 
        {
            frame = ValidationResult::InvalidChecksum;
            return;
        }

        frame = ValidationResult::Success;
        return;
    }
}
