/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

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

    void CreatingInstanceFromArraySucceeds()
    {
        std::vector<std::uint8_t> data { 0x01, 0x02, 0x03 };

        Rs485 sut(data.data(), 3);

        TEST_ASSERT_EQUAL_UINT8(0x01, static_cast<uint8_t>(sut[0]));
        TEST_ASSERT_EQUAL_UINT8(0x02, static_cast<uint8_t>(sut[1]));
        TEST_ASSERT_EQUAL_UINT8(0x03, static_cast<uint8_t>(sut[2]));
    }

    void AccessingDataWithIndexOperatorSucceeds()
    {
        std::vector<std::uint8_t> data { 0x01, 0x02, 0x03 };

        Rs485 sut(data);

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
}
