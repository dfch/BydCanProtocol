// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <Identifiers/BatteryChargeTotal.h>

namespace test::envNative::test_JkBms
{
    using namespace JkBms;
    using namespace JkBms::Identifiers;
    
    void BatteryChargeTotalIdentifierSucceeds(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x89,
            0x00, 0x00, 0x00, 0x00
        };

        auto sut = reinterpret_cast<BatteryChargeTotal*>(data.data());

        auto result = sut->Identifier.Value;

        TEST_ASSERT_EQUAL_UINT8(Id::BatteryChargeTotal, result);
    }

    void BatteryChargeTotalReturnsZero(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x89,
            0x00, 0x00, 0x00, 0x00
        };

        auto sut = reinterpret_cast<BatteryChargeTotal*>(data.data());

        auto result = sut->ToAmpereHour();

        TEST_ASSERT_EQUAL_FLOAT(0, result.Value.GetValue());
    }

    void BatteryChargeTotalReturns158965(void)
    {
        std::vector<std::uint8_t> data 
        {
            0x89,
            0x00, 0x02, 0x6C, 0xF5
        };

        auto sut = reinterpret_cast<BatteryChargeTotal*>(data.data());

        auto result = sut->ToAmpereHour();

        TEST_ASSERT_EQUAL(158965, result.Value.GetValue());
    }

    void SettingBatteryChargeTotalThrows(void)
    {
        BatteryChargeTotal sut;
        
        try
        {
            sut.FromAmpereHour(-1);
        }
        catch(...)
        {
            TEST_PASS();
            return;
        }
        TEST_FAIL();
    }
}
