/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <StateInfo.h>

extern "C"
{
    namespace test::envNative::test_Victron
    {
        void StateInfoTestSucceeds()
        {
            auto expected = true;

            auto result = true;

            TEST_ASSERT_EQUAL(expected, result);
        }
            
        int runUnityTestsStateInfo(void)
        {
            UNITY_BEGIN();

            RUN_TEST(StateInfoTestSucceeds);

            return UNITY_END();
        }
    }
}
