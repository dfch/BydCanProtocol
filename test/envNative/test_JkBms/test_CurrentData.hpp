// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <Identifiers/CurrentData.h>

namespace test::envNative::test_JkBms
{
    using namespace JkBms;
    using namespace JkBms::Identifiers;
    
    void TestingCurrentDataIdentifierSucceeds(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x84,
            0x00, 0x00
        };

        auto sut = reinterpret_cast<CurrentData*>(data.data());

        auto result = sut->Identifier.Value;

        TEST_ASSERT_EQUAL_UINT8(Id::CurrentData, result);
    }

    void TestingCurrentDataReturnsPlus5(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x84,
            0x25, 0x1C
        };

        auto sut = reinterpret_cast<CurrentData*>(data.data());

        auto result = sut->ToAmpere();

        TEST_ASSERT_EQUAL_FLOAT(5, result.Value.GetValue());
    }

    void TestingCurrentDataReturnsPlus100Dot53(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x84,
            0xFF, 0xCB
        };

        auto sut = reinterpret_cast<CurrentData*>(data.data());

        auto result = sut->ToAmpere();

        TEST_ASSERT_EQUAL_FLOAT(100.53, result.Value.GetValue());
    }

    void TestingCurrentDataReturnsZero(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x84,
            0x27, 0x10
        };

        auto sut = reinterpret_cast<CurrentData*>(data.data());

        auto result = sut->ToAmpere();

        TEST_ASSERT_EQUAL_FLOAT(0, result.Value.GetValue());
    }

    void TestingCurrentDataReturnsMinus10(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x84,
            0x2A, 0xF8
        };

        auto sut = reinterpret_cast<CurrentData*>(data.data());

        auto result = sut->ToAmpere();

        TEST_ASSERT_EQUAL_FLOAT(-10, result.Value.GetValue());
    }

    void TestingCurrentDataReturnsMinus2Dot98(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x84,
            0x28, 0x3A
        };

        auto sut = reinterpret_cast<CurrentData*>(data.data());

        auto result = sut->ToAmpere();

        TEST_ASSERT_EQUAL_FLOAT(-2.98, result.Value.GetValue());
    }
}
