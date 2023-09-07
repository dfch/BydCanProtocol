// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "Second.h"

namespace test::envNative::test_Units
{
    using namespace Units;

    void MilliSecondsInitialisingMillisecondsSucceeds()
    {
        MilliSecond sut(1'500'000);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(1'500'000, result);
    }

    void MilliSecondsGetValueToSecondRawReturns300()
    {
        MilliSecond sut(5 * 60 * 1000);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(300'000, result);
    }

    void MilliSecondsGetValueToSecondAsSameReturns300()
    {
        MilliSecond sut(5 * 60 * 1000);

        auto result = sut.GetValue<milli>();

        TEST_ASSERT_EQUAL_FLOAT(300'000, result);
    }

    void MilliSecondsGetValueToSecondsReturns300()
    {
        MilliSecond sut(5 * 60 * 1000);

        auto result = sut.GetValue<ToSeconds>();

        TEST_ASSERT_EQUAL_FLOAT(300, result);
    }

    void MilliSecondsGetValueToMinutesReturns5()
    {
        MilliSecond sut(5 * 60 * 1000);

        auto result = sut.GetValue<ToMinutes>();

        TEST_ASSERT_EQUAL_FLOAT(5, result);
    }

    void MilliSecondsGetValueToHoursSucceeds()
    {
        MilliSecond sut(30 * 60 * 1000);

        auto result = sut.GetValue<ToHours>();

        TEST_ASSERT_EQUAL_FLOAT(0.5, result);
    }

    void MilliSecondsGetValueToDaysSucceeds()
    {
        MilliSecond sut(12 * 60 * 60 * 1000);

        auto result = sut.GetValue<ToDays>();

        TEST_ASSERT_EQUAL_FLOAT(0.5, result);
    }

    void MilliSecondsSetValueRawSucceeds()
    {
        MilliSecond sut;
        sut.SetValue(1'500'000);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(1'500'000, result);
    }

    void MilliSecondsSetValueAsSameSucceeds()
    {
        MilliSecond sut;
        sut.SetValue<milli>(1'500'000);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(1'500'000, result);
    }

    void MilliSecondsSetValueFromMicroSucceeds()
    {
        MilliSecond sut;
        sut.SetValue<micro>(1'500'000);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(1'500, result);
    }

    void MilliSecondsSetValueFromSecondsSucceeds()
    {
        MilliSecond sut;
        sut.SetValue<FromSeconds>(1.5);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(1'500, result);
    }

    void MilliSecondsSetValueFromMinutesSucceeds()
    {
        MilliSecond sut;
        sut.SetValue<FromMinutes>(1);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(60'000, result);
    }

    void MilliSecondsSetValueFromHoursSucceeds()
    {
        MilliSecond sut;
        sut.SetValue<FromHours>(1);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(60 * 60'000, result);
    }

    void MilliSecondsSetValueFromDaysSucceeds()
    {
        MilliSecond sut;
        sut.SetValue<FromDays>(1);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(24 * 60 * 60'000, result);
    }

}