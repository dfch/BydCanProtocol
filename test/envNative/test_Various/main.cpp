// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_Thing.hpp"
#include "test_Vector.hpp"
#include "test_UniquePtr.hpp"

extern "C"
{
    namespace test::envNative::test_Various
    {
        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        int runUnityTests()
        {
            UNITY_BEGIN();

            // #include "test_Thing.hpp"
            RUN_TEST(MakeUniqueAccessingPrivateCtorSucceeds);

            // #include "test_Vector.hpp"
            RUN_TEST(TestVector);
            
            // #include "test_UniquePtr.hpp"
            RUN_TEST(InstantiatingCtorWithUniquePtrSucceeds);

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
