// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_Temperature.hpp"

extern "C"
{
    namespace test::envNative::test_Temperature
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

            RUN_TEST(GettingKelvinTemperatureSucceeds);
            RUN_TEST(SettingKelvinTemperatureSucceeds);
            RUN_TEST(SettingNegativeKelvinTemperatureThrows);
            RUN_TEST(GettingCelsiusTemperatureSucceeds);
            RUN_TEST(SettingCelsiusTemperatureSucceeds);
            RUN_TEST(ConvertingFromCelsiusToKelvinSucceeds);
            RUN_TEST(ConvertingFromCelsiusToKelvin2Succeeds);

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
