/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <Qword.h>

namespace test::envNative::test_Endian
{
    using namespace Endian;

    void IsLittleEndianSucceeds()
    {
        auto result = IsLittleEndian();

        TEST_ASSERT_TRUE(result);
    }
}
