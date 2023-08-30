/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>

namespace JkBms
{
    #pragma pack(push, 1)
    /// @brief As long as the 5- Bluetooth, 2- GPS, 3- PC host computer is initiated first, and the 4- BMS is initiated first, the reply is always 1.
    enum class TransmissionType : uint8_t
    {
        RequestFrame = 0x00, // Represents the request frame.
        ResponseFrame = 0x01, // Represents the response frame.
        ReportFrame = 0x02, // Represents the upload frame.
    };
    #pragma pack(pop)
}
