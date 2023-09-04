// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT


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
