// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <Identifiers/PowerManagementTemperature.h>

namespace test::envNative::test_JkBms
{
    using namespace JkBms;
    using namespace JkBms::Identifiers;
    
    void TestingPowerManagementTemperatureIdentifierSucceeds(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x80,
            0x00, 0x00
        };

        auto sut = reinterpret_cast<PowerManagementTemperature*>(data.data());

        auto result = sut->Identifier.Value;

        TEST_ASSERT_EQUAL_UINT8(Id::PowerManagementTemperature, result);
    }

    void TestingPowerManagementTemperatureWithInvalidMaximumThrows(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x80,
            0x00, 0x8D
        };

        auto sut = reinterpret_cast<PowerManagementTemperature*>(data.data());

        try
        {
            auto _ = sut->ToCelsius();
        }
        catch(const std::exception& ex)
        {
            TEST_PASS();
        }
    }

    void TestingPowerManagementTemperatureReturnsZero(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x80,
            0x00, 0x00
        };

        auto sut = reinterpret_cast<PowerManagementTemperature*>(data.data());

        auto result = sut->ToCelsius();

        TEST_ASSERT_EQUAL(0, result.GetValue());
    }

    void TestingPowerManagementTemperatureReturns100(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x80,
            0x00, 0x64
        };

        auto sut = reinterpret_cast<PowerManagementTemperature*>(data.data());

        auto result = sut->ToCelsius();

        TEST_ASSERT_EQUAL(100, result.GetValue());
    }

    void TestingPowerManagementTemperatureReturnsMinus1(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x80,
            0x00, 0x65
        };

        auto sut = reinterpret_cast<PowerManagementTemperature*>(data.data());

        auto result = sut->ToCelsius();

        TEST_ASSERT_EQUAL(-1, result.GetValue());
    }

    void TestingPowerManagementTemperatureReturnsMinus40(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x80,
            0x00, 0x8C
        };

        auto sut = reinterpret_cast<PowerManagementTemperature*>(data.data());

        auto result = sut->ToCelsius();

        TEST_ASSERT_EQUAL(-40, result.GetValue());
    }
}
