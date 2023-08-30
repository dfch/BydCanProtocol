/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

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

            // #include "test_AlarmWarning.hpp"
            RUN_TEST(ResetAllSucceeds);

            RUN_TEST(ResetAlarmsSucceeds);
            RUN_TEST(InitAlarmSucceeds);
            RUN_TEST(SetAlarmSucceeds);
            RUN_TEST(ResetAlarmSucceeds);

            RUN_TEST(ResetWarningsSucceeds);
            RUN_TEST(InitWarningSucceeds);
            RUN_TEST(SetWarningSucceeds);
            RUN_TEST(ResetWarningSucceeds);

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
