/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <Dvcc.h>

extern "C"
{
    namespace test::envNative::test_Victron
    {
        void DvccTestSucceeds()
        {
            auto expected = true;

            auto result = true;

            TEST_ASSERT_EQUAL(expected, result);
        }
            
        int runUnityTestsDvcc(void)
        {
            UNITY_BEGIN();

            RUN_TEST(DvccTestSucceeds);

            return UNITY_END();
        }
    }
}
