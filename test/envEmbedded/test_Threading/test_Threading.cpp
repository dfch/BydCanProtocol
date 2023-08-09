/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#include <unity.h>

#include <sys/time.h>

#include <Thread.h>

using Threading:Thread;

extern "C"
{
    namespace test::envEmbedded::test_Utils
    {
        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        void Sleep1000MillisecondsSucceeds()
        {
            // Arrange
            long expected = 1;

            struct timeval start;
            struct timeval stop;
            gettimeofday(&start, NULL);
            
            // Act
            Threading::Sleep(expected * 1000);

            // Assert
            gettimeofday(&stop, NULL);
            auto result = stop.tv_sec - start.tv_sec;
            
            TEST_ASSERT_EQUAL(expected, result);
        }

        int runUnityTests(void)
        {
            UNITY_BEGIN();

            RUN_TEST(Sleep1000MillisecondsSucceeds);

            return UNITY_END();
        }

        void app_main() 
        {
            runUnityTests();
        }
    }
}

#endif
