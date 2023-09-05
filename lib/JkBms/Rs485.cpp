// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include "Rs485.h"

#include <cstddef>

#include <Contract.h>

#include "Frame.h"

namespace JkBms
{
    using std::unique_ptr;
    using std::vector;
    using std::uint8_t;

    Rs485::Rs485(vector<uint8_t> &data)
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

    const Frame Rs485::GetFrame() const
    {
        Contract::Expects([this] { return this->frame.has_value(); }, "Invalid frame.");

        if(!frame.has_value()) return {};
        return *frame;
    }

    const std::map<Id, InformationUnit *>& Rs485::GetMessages() const
    {
        Contract::Expects([this] { return this->frame.has_value(); }, "Invalid frame.");

        return messages;
    }

    void Rs485::ParseData() noexcept
    {
        Frame result;

        const auto data = ptr.get();
        const auto frameSize = data->size();

        // Check minimum frame size.
        if(FrameSizeMinimum >= frameSize) 
        {
            frame = ValidationResult::FrameTooShort;
            return;
        }

        // Map data to header of frame.
        result.Header = reinterpret_cast<const Header*>(data->data());
        if(!result.Header->StartOfFrame.IsValid()) 
        {
            frame = ValidationResult::InvalidHeader;
            return;
        }

        // Check if length specified in header matches the frame size.
        if(result.Header->GetFrameLength() != frameSize) 
        {
            printf("Expected: %d (incl STX). Actual %d.\n", result.Header->GetFrameLength(), frameSize);
            frame = ValidationResult::InvalidLength;
            return;
        }
        
        // Calculate size of body.
        const auto bodySize = frameSize - FrameSizeMinimum;

        // Map data to body of frame.
        result.Body = reinterpret_cast<const InformationUnit*>(data->data() + sizeof(Header));
        if(!result.Body->Identifier.IsValid()) 
        {
            frame = ValidationResult::InvalidIdentifier;
            return;
        }

        // Map data to footer of frame.
        result.Footer = reinterpret_cast<const Footer*>(data->data() + sizeof(Header) + bodySize);
        if(!result.Footer->EndCode.IsValid())
        {
            frame = ValidationResult::InvalidEndCode;
            return;
        }

        // Calculate checksum.
        if(!result.IsValidChecksum()) 
        {
            frame = ValidationResult::InvalidChecksum;
            return;
        }

        // Extract all messages from Body into message.
        ParseMessages(const_cast<uint8_t&>(reinterpret_cast<const uint8_t&>(*result.Body)), bodySize);

        // Update contents for GetFrame(), GetMessages(), GetValidationResult().
        frame = result;
        
        return;
    }
}
