// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

namespace test::envNative::test_JkBms
{
    using namespace JkBms;
    
    void IsValidSucceeds()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame [00:01]
            0x00, 0x15, // Valid length [02:03]
            0x00, 0x00, 0x00, 0x00, // BMS terminal number [04:07]
            0x03, // Command word, [08]
            0x03, // Frame source, [09]
            0x00, // TransmissionType [10]
            
            // Body
            // arbitrary data here
            0x80,
            0x00, 0x64, // 100°C
            
            // Footer
            0x00, 0x00, 0x00, 0x00, // Record number
            0x68, // End code
            0x00, 0x00, 0x02, 0x0C // CRC
        };

        Rs485 sut(data);
        
        auto result = sut.IsValid();

        TEST_ASSERT_TRUE(result);
    }

    void IsValidFails()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame
            0x00, 0x00, // Length
            0xFF, 0xFF, 0xFF, 0xFF, // BMS terminal number
            0x03, // Command word,
            0x00, // Frame source,
            0x00, // TransmissionType
            
            // Body
            // ... empty here
            
            // Footer
            0x00, 0x11, 0x22, 0xAD, // Record number
            0x68, // End code
            0x12, 0x34, 0x56, 0x78 // CRC
        };

        Rs485 sut(data);

        auto result = sut.IsValid();

        TEST_ASSERT_FALSE(result);
    }

    void IsValidWithInvalidMinimumLengthFails()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame
            0x00, 0x00, // Length
            0xFF, 0xFF, 0xFF, 0xFF, // BMS terminal number
            0x03, // Command word,
            0x00, // Frame source,
            0x00, // TransmissionType
            
            // Body
            // ... empty here
            
            // Footer
            0x00, 0x11, 0x22, 0xAD, // Record number
            0x68, // End code
            0x12, 0x34, 0x56, 0x78 // CRC
        };

        Rs485 sut(data);

        auto result = sut.GetValidationResult();

        TEST_ASSERT_EQUAL_UINT8(ValidationResult::FrameTooShort, result);
    }

    void IsValidWithInvalidLengthFails()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame
            0x12, 0x34, // Invalid length
            0xFF, 0xFF, 0xFF, 0xFF, // BMS terminal number
            0x03, // Command word,
            0x00, // Frame source,
            0x00, // TransmissionType
            
            // Body
            // arbitrary data here
            0xCC, 0xBB, 0xCC, 0xBB,
            
            // Footer
            0x00, 0x11, 0x22, 0xAD, // Record number
            0x68, // End code
            0x12, 0x34, 0x56, 0x78 // CRC
        };

        Rs485 sut(data);

        auto result = sut.GetValidationResult();

        TEST_ASSERT_EQUAL_UINT8(ValidationResult::InvalidLength, result);
    }

    void IsValidWithValidLengthSucceeds()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame [00:01]
            0x00, 0x15, // Valid length [02:03]
            0xFF, 0xFF, 0xFF, 0xFF, // BMS terminal number [04:07]
            0x03, // Command word, [08]
            0x00, // Frame source, [09]
            0x00, // TransmissionType [10]
            
            // Body
            0x80,
            0x00, 0x64, // 100°C

            // Footer
            0x00, 0x11, 0x22, 0xAD, // Record number
            0x68, // End code
            0x00, 0x00, 0x06, 0xE5 // CRC
        };

        Rs485 sut(data);

        auto result = sut.GetValidationResult();

        TEST_ASSERT_EQUAL_UINT8(ValidationResult::Success, result);
    }

    void IsValidWithInvalidChecksumFails()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame [00:01]
            0x00, 0x16, // Valid length [02:03]
            0x00, 0x00, 0x00, 0x00, // BMS terminal number [04:07]
            0x03, // Command word, [08]
            0x00, // Frame source, [09]
            0x01, // TransmissionType [10]
            
            // Body
            // arbitrary data here
            0x00, 0x12, 0x34, 0x56, // [11:14]
            
            // Footer
            0x00, 0x11, 0x22, 0xAD, // Record number [15:18]
            0x68, // End code [19]
            0x00, 0x00, 0x12, 0x34 // CRC [20:23] invalid
        };

        Rs485 sut(data);

        auto result = sut.GetValidationResult();

        TEST_ASSERT_EQUAL_UINT8(ValidationResult::InvalidChecksum, result);
    }

    void IsValidWithValidChecksumSucceeds()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame [00:01]
            0x00, 0x15, // Valid length [02:03]
            0x00, 0x00, 0x00, 0x00, // BMS terminal number [04:07]
            0x03, // Command word, [08]
            0x03, // Frame source, [09]
            0x00, // TransmissionType [10]
            
            // Body
            // arbitrary data here
            0x80,
            0x00, 0x64, // 100°C
            
            // Footer
            0x00, 0x00, 0x00, 0x00, // Record number
            0x68, // End code
            0x00, 0x00, 0x02, 0x0C // CRC
        };

        Rs485 sut(data);

        auto result = sut.GetValidationResult();

        TEST_ASSERT_EQUAL_UINT8(ValidationResult::Success, result);
    }

    void IsValidWithInvalidIdentifierFails()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame [00:01]
            0x00, 0x13, // Valid length [02:03]
            0x00, 0x00, 0x00, 0x00, // BMS terminal number [04:07]
            0x03, // Command word, [08]
            0x03, // Frame source, [09]
            0x00, // TransmissionType [10]
            
            // Body
            // arbitrary data here
            0x01,  // [11]
            
            // Footer
            0x00, 0x00, 0x00, 0x00, // Record number [12:15]
            0x68, // End code [16]
            0x00, 0x00, 0x01, 0x2A // CRC [17:20]
        };

        Rs485 sut(data);

        auto result = sut.GetValidationResult();

        TEST_ASSERT_EQUAL_UINT8(ValidationResult::InvalidIdentifier, result);
    }

    void GettingMessagesSucceeds()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame [00:01]
            0x00, 34 - sizeof(StartOfFrame), // Valid length [02:03]
            0x00, 0x00, 0x00, 0x00, // BMS terminal number [04:07]
            0x03, // Command word, [08]
            0x03, // Frame source, [09]
            0x00, // TransmissionType [10]
            
            // Body
            (uint8_t) Id::CellVoltage, // Battery voltage.
            4 * 3, // Number of cells multiplied by size of cell information.
            0x01, 0x0E, 0xED, // 3821 * 0.001 = 3.821V
            0x02, 0x0E, 0xFA, // 3834 * 0.001 = 3.834V
            0x03, 0x0E, 0xF7, // 3831 * 0.001 = 3.831V
            0x04, 0x0E, 0xEC, // 3820 * 0.001 = 3.820V
            
            // Footer
            0x00, 0x00, 0x00, 0x00, // Record number [12:15]
            0x68, // End code [16]
            0x00, 0x00, 0x05, 0xC4 // CRC [17:20]
        };
        TEST_ASSERT_EQUAL(34, data.size());

        Rs485 sut(data);

        TEST_ASSERT_TRUE(sut.IsValid());

        auto result = sut.GetMessages();

        TEST_ASSERT_EQUAL(1, result.size());
        TEST_ASSERT_EQUAL(Id::CellVoltage, result.begin()->first);
    }

    void GettingMultipleMessagesSucceeds()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame [00:01]
            0x00, 37 - sizeof(StartOfFrame), // Valid length [02:03]
            0x00, 0x00, 0x00, 0x00, // BMS terminal number [04:07]
            0x06, // Command word, [08]
            0x03, // Frame source, [09]
            0x00, // TransmissionType [10]
            
            // Body
            // 1st message
            (uint8_t) Id::CellVoltage,
            4 * 3, // Number of cells multiplied by size of cell information.
            0x01, 0x0E, 0xED, // 3821 * 0.001 = 3.821V
            0x02, 0x0E, 0xFA, // 3834 * 0.001 = 3.834V
            0x03, 0x0E, 0xF7, // 3831 * 0.001 = 3.831V
            0x04, 0x0E, 0xEC, // 3820 * 0.001 = 3.820V
            // 2nd message
            (uint8_t) Id::BmsTemperature,
            0x00, 0x64, // 100°C
            
            // Footer
            0x00, 0x00, 0x00, 0x00, // Record number [12:15]
            0x68, // End code [16]
            0x00, 0x00, 0x06, 0xAE // CRC [17:20]
        };
        TEST_ASSERT_EQUAL(37, data.size());

        Rs485 sut(data);
        TEST_ASSERT_EQUAL(ValidationResult::Success, sut.GetValidationResult());

        auto result = sut.GetMessages();

        TEST_ASSERT_EQUAL(2, result.size());
        TEST_ASSERT_EQUAL(Id::CellVoltage, result.begin()->first);
        TEST_ASSERT_EQUAL(Id::BmsTemperature, result.rbegin()->first);
    }
}
