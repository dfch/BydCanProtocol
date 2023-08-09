/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <Generator.h>

using MorseCode::Generator;
using MorseCode::Configuration;
using MorseCode::Signal;

extern "C"
{
    namespace test::envNative::test_MorseCode
    {
        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        void SerialiseReturnsCorrectVectorSize(void)
        {
            // Arrange
            auto configuration = std::make_shared<Configuration>();
            configuration->Transmit = [](int ms) { return; };
            configuration->NoTransmit = [](int ms) { return; };

            std::string message = "sos";

            auto sut = std::make_shared<Generator>(configuration);

            // Act
            auto result = sut->Serialise(message);

            // Assert
            TEST_ASSERT_EQUAL(3+1 + 3+1 + 3+1 +1, result.size());
        }

        void SerialiseReturnsCorrectVectorContent(void)
        {
            // Arrange
            auto configuration = std::make_shared<Configuration>();
            configuration->Transmit = [](int ms) { return; };
            configuration->NoTransmit = [](int ms) { return; };

            std::string message = "sos";

            auto sut = std::make_shared<Generator>(configuration);

            // Act
            auto result = sut->Serialise(message);

            // Assert
            TEST_ASSERT_EQUAL(MorseCode::Dit, result[0]);
            TEST_ASSERT_EQUAL(MorseCode::Dit, result[1]);
            TEST_ASSERT_EQUAL(MorseCode::Dit, result[2]);
            
            TEST_ASSERT_EQUAL(MorseCode::Char, result[3]);

            TEST_ASSERT_EQUAL(MorseCode::Dah, result[4]);
            TEST_ASSERT_EQUAL(MorseCode::Dah, result[5]);
            TEST_ASSERT_EQUAL(MorseCode::Dah, result[6]);

            TEST_ASSERT_EQUAL(MorseCode::Char, result[7]);

            TEST_ASSERT_EQUAL(MorseCode::Dit, result[8]);
            TEST_ASSERT_EQUAL(MorseCode::Dit, result[9]);
            TEST_ASSERT_EQUAL(MorseCode::Dit, result[10]);
            
            TEST_ASSERT_EQUAL(MorseCode::Char, result[11]);

            TEST_ASSERT_EQUAL(MorseCode::Word, result[12]);
        }

        int runUnityTests(void)
        {
            UNITY_BEGIN();

            RUN_TEST(SerialiseReturnsCorrectVectorSize);
            RUN_TEST(SerialiseReturnsCorrectVectorContent);

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
