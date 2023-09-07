// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>
#include <ratio>

#include "Value.h"

namespace test::envNative::test_Units
{
    using namespace Units;

    void InitialisingValueTSucceeds()
    {
        ValueT<int, std::milli> sut(1'500);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL(1'500, result);
    }

    void GetValueAsSameSucceeds()
    {
        ValueT<int, std::milli> sut(1'500);

        auto result = sut.GetValue<std::milli>();

        TEST_ASSERT_EQUAL(1'500, result);
    }

    void GetValueAsMicroSucceeds()
    {
        ValueT<int, std::milli> sut(1'500);

        auto result = sut.GetValue<std::micro>();

        TEST_ASSERT_EQUAL(1'500'000, result);
    }

    void SetValueAsSameSucceeds()
    {
        ValueT<int, std::milli> sut;

        sut.SetValue<std::milli>(1'500);
        
        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL(1'500, result);
    }

    void SetValueAsMicroSucceeds()
    {
        ValueT<float, std::milli> sut;

        sut.SetValue<std::micro>(1'500'000);
        
        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL(1'500, result);
    }

}