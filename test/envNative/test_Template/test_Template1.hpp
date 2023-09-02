/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <Rs485.h>

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
