// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <Rs485.h>
#include <Frame.h>
#include <Qword.h>

namespace test::envNative::test_JkBms
{
    using namespace JkBms;
    
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

        TEST_ASSERT_EQUAL_UINT8(0x79, sut->Identifier.Value);
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
