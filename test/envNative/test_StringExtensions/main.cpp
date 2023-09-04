// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_StringExtensions.hpp"

extern "C"
{
    namespace test::envNative::test_StringExtensions
    {
        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        int runUnityTests(void)
        {
            UNITY_BEGIN();

            RUN_TEST(StringTrimWhitespaceSucceeds);
            RUN_TEST(StringTrimCharSucceeds);
            RUN_TEST(StringToLowerSucceeds);
            RUN_TEST(StringToUpperSucceeds);
            
            return UNITY_END();
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
