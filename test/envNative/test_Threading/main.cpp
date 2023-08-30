/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include "test_Threading.hpp"

extern "C"
{
    namespace test::envNative::test_Threading
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

            RUN_TEST(RetrySucceeds);

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
