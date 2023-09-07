// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "Second.h"

namespace test::envNative::test_Units
{
    using namespace Units;

    void ScaleToSecondsReturns42()
    {
        MicroSecond sut(42'000'000);

        auto result = sut.GetValue<ToSeconds>();

        TEST_ASSERT_EQUAL_FLOAT(42, result);
    }

    void ScaleToSecondsReturnsM42()
    {
        MicroSecond sut(-42'000'000);

        auto result = sut.GetValue<ToSeconds>();

        TEST_ASSERT_EQUAL_FLOAT(-42, result);
    }

    void ScaleToMillisecondsReturns1500()
    {
        MicroSecond sut(1'500'000);

        auto result = sut.GetValue<milli>();

        TEST_ASSERT_EQUAL_FLOAT(1'500, result);
    }

    void ScaleToMillisecondsReturnsM1500()
    {
        MicroSecond sut(-1'500'000);

        auto result = sut.GetValue<milli>();

        TEST_ASSERT_EQUAL_FLOAT(-1'500, result);
    }

    void ScaleToHoursReturns3()
    {
        MicroSecond sut((int64_t) 3 * 60 * 60 * 1'000'000);

        auto result = sut.GetValue<ToHours>();

        TEST_ASSERT_EQUAL_FLOAT(3, result);
    }

    void ScaleToMinutesReturns210()
    {
        MicroSecond sut((int64_t) 3 * 60 * 60 * 1'000'000 + 30 * 60 * 1'000'000);

        auto result = sut.GetValue<ToMinutes>();

        TEST_ASSERT_EQUAL_FLOAT(210, result);
    }

    void SetValueWithRatioReturns1500000()
    {
        MicroSecond sut;
        sut.SetValue<milli>(1'500);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(1'500'000, result);
    }
}
