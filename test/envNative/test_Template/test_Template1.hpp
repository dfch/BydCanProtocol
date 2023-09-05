// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

namespace test::envNative::test_Template
{
    // using namespace Template;
    
    void TestingSucceeds()
    {
        auto actual = 42;

        auto sut(actual);

        auto result = sut;

        TEST_ASSERT_EQUAL(actual, result);
    }
}
