// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_Template1.hpp"

extern "C"
{
    // Run tests for this folder by running this command:
    // [path-to-platformio]platformio.exe test --environment [your-env] --verbose --filter */test_Template
    namespace test::envNative::test_Template
    {
        // using namespace Template;
        
        int runUnityTests()
        {
            UNITY_BEGIN();

            // #include "test_Template1.hpp"
            RUN_TEST(TestingSucceeds);

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
