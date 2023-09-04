// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>
#include <vector>
#include <stdexcept>

#include <Rs485.h>

namespace test::envNative::test_JkBms
{
    using namespace JkBms;
    
    void CreatingInstanceFromVectorSucceeds()
    {
        std::vector<std::uint8_t> data { 0x01, 0x02, 0x03 };

        Rs485 sut(data);

        TEST_ASSERT_EQUAL_UINT8(0x01, static_cast<uint8_t>(sut[0]));
        TEST_ASSERT_EQUAL_UINT8(0x02, static_cast<uint8_t>(sut[1]));
        TEST_ASSERT_EQUAL_UINT8(0x03, static_cast<uint8_t>(sut[2]));
    }

    void CreatingInstanceFromUniquePtrVectorSucceeds()
    {
        std::vector<std::uint8_t> data { 0x01, 0x02, 0x03 };

        auto ptr = std::make_unique<std::vector<uint8_t>>(std::move(data));

        Rs485 sut(std::move(ptr));

        TEST_ASSERT_EQUAL_UINT8(0x01, static_cast<uint8_t>(sut[0]));
        TEST_ASSERT_EQUAL_UINT8(0x02, static_cast<uint8_t>(sut[1]));
        TEST_ASSERT_EQUAL_UINT8(0x03, static_cast<uint8_t>(sut[2]));
    }

    void AccessingDataWithInvalidIndexThrows()
    {
        std::vector<std::uint8_t> data { 0x01, 0x02, 0x03 };

        Rs485 sut(data);

        try
        {
            std::ignore = sut[3];
        }
        catch(const std::invalid_argument& ex)
        {
            std::basic_string result (ex.what());

            TEST_ASSERT_TRUE(std::string::npos != result.find("0x0003"));
        }
    }

    void GettingLengthSucceeds()
    {
        std::vector<std::uint8_t> data { 0x01, 0x02, 0x03 };

        Rs485 sut(data);

        auto result = sut.Length();

        TEST_ASSERT_EQUAL(3, result);
    }

    void GettingDataSucceeds()
    {
        std::vector<std::uint8_t> data { 0x01, 0x02, 0x03 };

        Rs485 sut(data);

        auto result = sut.Data();

        TEST_ASSERT_EQUAL_UINT8(0x01, result[0]);
        TEST_ASSERT_EQUAL_UINT8(0x02, result[1]);
        TEST_ASSERT_EQUAL_UINT8(0x03, result[2]);
    }

    void InstantiatingMovesVectorMemory()
    {
        std::vector<std::uint8_t> data { 0x01, 0x02, 0x03 };

        Rs485 sut(data);

        TEST_ASSERT_EQUAL(0, data.size());
    }
}
