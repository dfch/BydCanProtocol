// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_Endian.hpp"

extern "C"
{
    namespace test::envNative::test_Endian
    {
        int runUnityTests()
        {
            UNITY_BEGIN();

            RUN_TEST(IsLittleEndianSucceeds);
            RUN_TEST(ConvertingBackAndForthSucceeds);

            return UNITY_END();
        }

        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        void app_main() 
        {
            runUnityTests();
        }

        int main(int argc, char **argv)
        {
            return runUnityTests();
        }
    }
}
