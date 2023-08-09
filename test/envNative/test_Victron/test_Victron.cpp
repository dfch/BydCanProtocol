/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include "test_Dvcc.hpp"
#include "test_StateInfo.hpp"
#include "test_AlarmWarning.hpp"

extern "C"
{
    namespace test::envNative::test_Victron
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

            runUnityTestsDvcc();
            runUnityTestsStateInfo();
            runUnityTestsAlarmWarning();

            return 0;
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
