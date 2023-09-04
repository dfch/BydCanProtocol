// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_Units.hpp"

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

            RUN_TEST(InitialisingAndScalingUnitSucceeds);
            
            RUN_TEST(InitialisingVoltSucceeds);
            RUN_TEST(ScalingVoltSucceeds);
            RUN_TEST(RoundingVoltSucceeds);
            RUN_TEST(ScalingVoltToCentiSucceeds);
            
            RUN_TEST(ScalingAmpereToMicroSucceeds);
            RUN_TEST(ScalingAmpereToDeciSucceeds);
            RUN_TEST(ScalingAmpereNegativeToDeciSucceeds);
            RUN_TEST(ScalingAmpereNegativeToDeciAndRoundToInt16Succeeds);

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
