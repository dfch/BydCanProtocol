/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <Rs485.h>
#include <Frame.h>
#include <Qword.h>

namespace test::envNative::test_JkBms
{
    using namespace JkBms;
    
    void IsValidWithInvalidMinimumLengthFails()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame
            0x00, 0x00, // Length
            0xFF, 0xFF, 0xFF, 0xFF, // BMS terminal number
            0x00, // Command word,
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
            0x00, // Command word,
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

        auto result = sut.IsValid();

        TEST_ASSERT_EQUAL_UINT8(ValidationResult::InvalidLength, result);
    }

    void IsValidWithValidLengthSucceeds()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame [00:01]
            0x00, 0x13, // Valid length [02:03]
            0xFF, 0xFF, 0xFF, 0xFF, // BMS terminal number [04:07]
            0x00, // Command word, [08]
            0x00, // Frame source, [09]
            0x00, // TransmissionType [10]
            
            // Body
            0x00,
            
            // Footer
            0x00, 0x11, 0x22, 0xAD, // Record number
            0x68, // End code
            0x00, 0x00, 0x05, 0xFC // CRC
        };

        Rs485 sut(data);

        auto result = sut.IsValid();

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
            0x06, // Command word, [08]
            0x00, // Frame source, [09]
            0x01, // TransmissionType [10]
            
            // Body
            // arbitrary data here
            0xCC, 0xBB, 0xCC, 0xBB, // [11:14]
            
            // Footer
            0x00, 0x11, 0x22, 0xAD, // Record number [15:18]
            0x68, // End code [19]
            0x00, 0x00, 0x12, 0x34 // CRC [20:23]
        };

        Rs485 sut(data);

        auto result = sut.IsValid();

        TEST_ASSERT_EQUAL_UINT8(ValidationResult::InvalidChecksum, result);
    }

    void IsValidWithValidChecksumSucceeds()
    {
        std::vector<std::uint8_t> data 
        { 
            // Header
            0x4E, 0x57, // StartOfFrame [00:01]
            0x00, 0x13, // Valid length [02:03]
            0x00, 0x00, 0x00, 0x00, // BMS terminal number [04:07]
            0x06, // Command word, [08]
            0x03, // Frame source, [09]
            0x00, // TransmissionType [10]
            
            // Body
            // arbitrary data here
            0x00,  // [11]
            
            // Footer
            0x00, 0x00, 0x00, 0x00, // Record number [12:15]
            0x68, // End code [16]
            0x00, 0x00, 0x01, 0x29 // CRC [17:20]
        };

        Rs485 sut(data);

        auto result = sut.IsValid();

        TEST_ASSERT_EQUAL_UINT8(ValidationResult::Success, result);
    }

    void TestingCellVoltageSucceeds(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x79, // Battery voltage.
            4 * 3, // Number of cells multiplied by size of cell information.
            0x01, 0x0E, 0xED, // 3821 * 0.001 = 3.821V
            0x02, 0x0E, 0xFA, // 3834 * 0.001 = 3.834V
            0x03, 0x0E, 0xF7, // 3831 * 0.001 = 3.831V
            0x04, 0x0E, 0xEC, // 3820 * 0.001 = 3.820V
        };

        auto sut = reinterpret_cast<CellVoltage*>(data.data());

        TEST_ASSERT_EQUAL_UINT8(0x79, sut->Identifier);
        TEST_ASSERT_EQUAL_UINT16(4 * 3, sut->Length);
        TEST_ASSERT_EQUAL(4, sut->CellCount());
        
        auto c00 = sut->CellInfos[0];
        TEST_ASSERT_EQUAL_UINT8(1, c00.Number.Value);
        TEST_ASSERT_EQUAL(3821, c00.MilliVolt.ToLittleEndian());
        
        auto c01 = sut->CellInfos[1];
        TEST_ASSERT_EQUAL_UINT8(2, c01.Number.Value);
        TEST_ASSERT_EQUAL(3834, c01.MilliVolt.ToLittleEndian());

        auto c02 = sut->CellInfos[2];
        TEST_ASSERT_EQUAL_UINT8(3, c02.Number.Value);
        TEST_ASSERT_EQUAL(3831, c02.MilliVolt.ToLittleEndian());

        auto c03 = sut->CellInfos[3];
        TEST_ASSERT_EQUAL_UINT8(4, c03.Number.Value);
        TEST_ASSERT_EQUAL(3820, c03.MilliVolt.ToLittleEndian());

        auto result = sut->GetAverageVoltageMilliVolt();
        TEST_ASSERT_EQUAL_UINT16((3821 + 3834 + 3831 + 3820) / 4, result);
    }
}
