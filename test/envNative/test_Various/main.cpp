/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include "test_Thing.hpp"
#include "test_Vector.hpp"

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

            RUN_TEST(MakeUniqueAccessingPrivateCtorSucceeds);

            RUN_TEST(TestVector);

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
