/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include "test_Expected.hpp"

extern "C"
{
    namespace test::envNative::test_Expected
    {
        using namespace Expected;
        
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

            // #include "test_Expected.hpp"
            RUN_TEST(InitialisingExpectedWithValueSucceeds);
            RUN_TEST(InitialisingExpectedAndAssigningValueSucceeds);
            RUN_TEST(InitialisingExpectedWithoutValueOrUnexpectedThrows);
            RUN_TEST(InitialisingExpectedWithoutValueWithUnexpectedSucceeds);

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
