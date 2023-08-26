/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>
#include <iostream>
#include <stdexcept>

#include <Rs485.h>

using namespace JkBms;

extern "C"
{
    namespace test::envNative::test_JkBms
    {
        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        void CreatingInstanceFromVectorOfByteSucceeds(void)
        {
            std::vector<std::byte> data = { std::byte{ 0x01 }, std::byte{ 0x02 }, std::byte{ 0x03 } };

            auto sut(data);

            TEST_ASSERT_EQUAL_UINT8(0x01, static_cast<uint8_t>(sut[0]));
            TEST_ASSERT_EQUAL_UINT8(0x02, static_cast<uint8_t>(sut[1]));
            TEST_ASSERT_EQUAL_UINT8(0x03, static_cast<uint8_t>(sut[2]));
        }

        void CreatingInstanceFromByteArraySucceeds(void)
        {
            std::byte data[] = { std::byte{ 0x01 }, std::byte{ 0x02 }, std::byte{ 0x03 } };

            JkBms::Rs485 sut(data, 3);

            TEST_ASSERT_EQUAL_UINT8(0x01, static_cast<uint8_t>(sut[0]));
            TEST_ASSERT_EQUAL_UINT8(0x02, static_cast<uint8_t>(sut[1]));
            TEST_ASSERT_EQUAL_UINT8(0x03, static_cast<uint8_t>(sut[2]));
        }

        void AccessingDataWithIndexOperatorSucceeds(void)
        {
            std::vector<std::byte> data = { std::byte{ 0x01 }, std::byte{ 0x02 }, std::byte{ 0x03 } };

            auto sut(data);

            TEST_ASSERT_EQUAL_UINT8(0x01, static_cast<uint8_t>(sut[0]));
            TEST_ASSERT_EQUAL_UINT8(0x02, static_cast<uint8_t>(sut[1]));
            TEST_ASSERT_EQUAL_UINT8(0x03, static_cast<uint8_t>(sut[2]));
        }

        void AccessingDataWithInvalidIndexThrows(void)
        {
            std::vector<std::byte> data = { std::byte{ 0x01 }, std::byte{ 0x02 }, std::byte{ 0x03 } };

            auto sut(data);

            try
            {
                auto _ = sut[3];
            }
            catch(const std::invalid_argument& ex)
            {
                std::basic_string result (ex.what());

                TEST_ASSERT_TRUE(std::string::npos != result.find("0x0003"));
            }
        }

        int runUnityTests(void)
        {
            UNITY_BEGIN();

            RUN_TEST(CreatingInstanceFromVectorOfByteSucceeds);
            RUN_TEST(AccessingDataWithIndexOperatorSucceeds);
            RUN_TEST(AccessingDataWithInvalidIndexThrows);

            return UNITY_END();
        }

        void app_main() 
        {
            runUnityTests();
        }

        int main(int argc, char **argv)
        {
            return runUnityTests();
        }
    }
}
