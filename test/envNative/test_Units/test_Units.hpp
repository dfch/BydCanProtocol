// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "Scale.h"
#include "Value.h"
#include "Volt.h"
#include "Ampere.h"
#include "AmpereHour.h"
#include "Watt.h"
#include "WattHour.h"

namespace test::envNative::test_Units
{
    void InitialisingAndScalingUnitSucceeds()
    {
        auto value = 20'000;
        auto expected = value / 100;
        Units::Unit sut(value);

        auto result = sut.Value.ScaleTo(Units::Scale::Hecto);

        TEST_ASSERT_EQUAL(expected, result);
    }

    void InitialisingVoltSucceeds()
    {
        auto value = 58.4;
        auto expected = value * 1000;
        Units::Volt sut(value);

        auto result = sut.Value.ScaleTo(Units::Scale::Milli, true);

        TEST_ASSERT_EQUAL(expected, result);
    }

    void ScalingVoltSucceeds()
    {
        auto value = 58.4;
        auto expected = value / 10;
        Units::Volt sut(value);

        auto result = sut.Value.ScaleTo(Units::Scale::Deka, false);

        TEST_ASSERT_EQUAL_FLOAT(expected, result);
    }

    void RoundingVoltSucceeds()
    {
        auto value = 58.4;
        auto expected = 58;
        Units::Volt sut(value);

        auto result = sut.Value.ScaleTo(Units::Scale::Default, true);

        TEST_ASSERT_EQUAL_FLOAT(expected, result);
    }

    void ScalingAmpereToMicroSucceeds()
    {
        auto value = 52.3;
        auto expected = value * 1'000'000;
        Units::Volt sut(value);

        auto result = sut.Value.ScaleTo(Units::Scale::Micro);

        TEST_ASSERT_EQUAL_FLOAT(expected, result);
    }

    void ScalingVoltToCentiSucceeds()
    {
        auto value = 53.1;
        auto expected = value * 100;
        Units::Volt sut(value);

        auto result = sut.Value.ScaleTo(Units::Scale::Centi);

        TEST_ASSERT_EQUAL_FLOAT(expected, result);
    }

    void ScalingAmpereToDeciSucceeds()
    {
        auto value = 0.7;
        auto expected = value * 10;
        Units::Ampere sut(value);

        auto result = sut.Value.ScaleTo(Units::Scale::Deci);

        TEST_ASSERT_EQUAL_FLOAT(expected, result);
    }

    typedef union tagInt16
    {
        std::int16_t Integer;
        std::byte Bytes[2];
    } Int16;

    void ScalingAmpereNegativeToDeciSucceeds()
    {
        auto value = -0.7;
        auto expected = value * 10;
        Units::Ampere sut(value);

        auto result = sut.Value.ScaleTo(Units::Scale::Deci);

        TEST_ASSERT_EQUAL_FLOAT(expected, result);
    }

    typedef union tagInteger16
    {
        std::int16_t Integer16;
        std::byte Bytes[2];
    } Integer16;

    void ScalingAmpereNegativeToDeciAndRoundToInt16Succeeds()
    {
        auto value = -0.7;
        Units::Ampere sut(value);

        Integer16 result;
        result.Integer16 = sut.Value.ScaleTo(Units::Scale::Deci, true);

        TEST_ASSERT_EQUAL_HEX8(0xF9, result.Bytes[0]);
        TEST_ASSERT_EQUAL_HEX8(0xFF, result.Bytes[1]);
    }
} 
