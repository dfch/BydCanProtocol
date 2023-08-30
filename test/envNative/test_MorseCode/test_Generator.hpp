/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <Generator.h>

namespace test::envNative::test_MorseCode
{
    using namespace MorseCode;

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
}
