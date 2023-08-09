/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#include <unity.h>

#include <Pin.h>

using Gpio::Pin;

extern "C"
{
    namespace test::envEmbedded::test_Pin
    {
        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        void SettingLedHighSucceeds()
        {
            auto state = true;
            auto sut = new Pin(LED, GPIO_MODE_OUTPUT);

            sut->Set(state);

            auto result = sut->Get();
            TEST_ASSERT_EQUAL(false, result);

            TEST_PASS();
        }

        void SettingLedLowSucceeds()
        {
            auto state = false;
            auto sut = new Pin(LED, GPIO_MODE_OUTPUT);

            sut->Set(state);

            auto result = sut->Get();
            TEST_ASSERT_EQUAL(false, result);
        }

        int runUnityTests(void)
        {
            UNITY_BEGIN();

            RUN_TEST(SettingLedHighSucceeds);
            RUN_TEST(SettingLedLowSucceeds);

            return UNITY_END();
        }

        void app_main() 
        {
            runUnityTests();
        }
    }
}

#endif
