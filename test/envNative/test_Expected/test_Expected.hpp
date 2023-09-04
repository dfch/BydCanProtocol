// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>
#include <cstdint>

#ifdef __cpp_lib_expected
    #include <expected>
#else
    #include "Expected.h"
#endif

namespace test::envNative::test_Expected
{
    using namespace Expected;

    enum class Status : uint8_t
    {
        Error0,
        Error1,
    };

    void InitialisingExpectedWithValueSucceeds()
    {
        int value = 1;

        expected<int, Status> sut(value);

        TEST_ASSERT_TRUE(sut.has_value());
        
        auto result = *sut;

        TEST_ASSERT_EQUAL(value, result);
    }

    void InitialisingExpectedAndAssigningValueSucceeds()
    {
        int value = 1;

        expected<int, Status> sut;
        TEST_ASSERT_FALSE(sut.has_value());

        sut = value;

        TEST_ASSERT_TRUE(sut.has_value());
        
        auto result = *sut;

        TEST_ASSERT_EQUAL(value, result);
    }

    void InitialisingExpectedWithoutValueOrUnexpectedThrows()
    {
        int value = 1;

        expected<int, Status> sut;

        TEST_ASSERT_FALSE(sut.has_value());
        
        try
        {
            auto result = sut.error();
        }
        catch(...)
        {
            TEST_PASS();
        }

        TEST_FAIL();
    }

    void InitialisingExpectedWithoutValueWithUnexpectedSucceeds()
    {
        expected<int, Status> sut;

        TEST_ASSERT_FALSE(sut.has_value());

        sut = Status::Error1;        
        TEST_ASSERT_FALSE(sut.has_value());
        
        auto result = sut.error();

        TEST_ASSERT_EQUAL(Status::Error1, result);
    }
}
