// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "Second.h"

namespace test::envNative::test_Units
{
    using namespace Units;

    void SecondInitialisingSucceeds()
    {
        Second sut(1.5);

        auto result = sut.GetValue<micro>();

        TEST_ASSERT_EQUAL_FLOAT(1'500'000, result);
    }

    void SecondSetValueFromMilliSucceeds()
    {
        Second sut;

        sut.SetValue<milli>(1'500);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(1.5, result);
    }

    void MinuteInitialisingSucceeds()
    {
        Minute sut(1.5);

        auto result = sut.GetValue<milli>();

        TEST_ASSERT_EQUAL_FLOAT(90'000, result);
    }

    void MinuteSetValueFromMilliSucceeds()
    {
        Minute sut;

        sut.SetValue<milli>(1'500'000);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(25, result);
    }

    void HourInitialisingSucceeds()
    {
        Hour sut(1.5);

        auto result = sut.GetValue<ToMinutes>();

        TEST_ASSERT_EQUAL_FLOAT(90, result);
    }

    void HourSetValueFromMilliSucceeds()
    {
        Hour sut;

        sut.SetValue<milli>(1'440'000'000);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL_FLOAT(400, result);
    }
}
