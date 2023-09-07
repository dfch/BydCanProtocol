// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_Units.hpp"
#include "test_Microsecond.hpp"
#include "test_Millisecond.hpp"
#include "test_ValueT.hpp"

extern "C"
{
    namespace test::envNative::test_Units
    {
        int runUnityTests(void)
        {
            UNITY_BEGIN();

            // #include "test_Units.hpp"
            RUN_TEST(InitialisingAndScalingUnitSucceeds);
            
            RUN_TEST(InitialisingVoltSucceeds);
            RUN_TEST(ScalingVoltSucceeds);
            RUN_TEST(RoundingVoltSucceeds);
            RUN_TEST(ScalingVoltToCentiSucceeds);
            
            RUN_TEST(ScalingAmpereToMicroSucceeds);
            RUN_TEST(ScalingAmpereToDeciSucceeds);
            RUN_TEST(ScalingAmpereNegativeToDeciSucceeds);
            RUN_TEST(ScalingAmpereNegativeToDeciAndRoundToInt16Succeeds);

            // #include "test_Microsecond.hpp"
            RUN_TEST(ScaleToSecondsReturns42);
            RUN_TEST(ScaleToSecondsReturnsM42);
            RUN_TEST(ScaleToMillisecondsReturns1500);
            RUN_TEST(ScaleToMillisecondsReturnsM1500);
            RUN_TEST(ScaleToHoursReturns3);
            RUN_TEST(ScaleToMinutesReturns210);
            RUN_TEST(SetValueWithRatioReturns1500000);
            
            RUN_TEST(SecondInitialisingSucceeds);
            RUN_TEST(SecondSetValueFromMilliSucceeds);
            RUN_TEST(MinuteInitialisingSucceeds);
            RUN_TEST(MinuteSetValueFromMilliSucceeds);
            RUN_TEST(HourInitialisingSucceeds);
            RUN_TEST(HourSetValueFromMilliSucceeds);

            // #include "test_Millisecond.hpp"
            RUN_TEST(MilliSecondsInitialisingMillisecondsSucceeds);
            RUN_TEST(MilliSecondsGetValueToSecondRawReturns300);
            RUN_TEST(MilliSecondsGetValueToSecondAsSameReturns300);
            RUN_TEST(MilliSecondsGetValueToSecondsReturns300);
            RUN_TEST(MilliSecondsGetValueToMinutesReturns5);
            RUN_TEST(MilliSecondsGetValueToHoursSucceeds);
            RUN_TEST(MilliSecondsGetValueToDaysSucceeds);
            RUN_TEST(MilliSecondsSetValueRawSucceeds);
            RUN_TEST(MilliSecondsSetValueAsSameSucceeds);
            RUN_TEST(MilliSecondsSetValueFromMicroSucceeds);
            RUN_TEST(MilliSecondsSetValueFromSecondsSucceeds);
            RUN_TEST(MilliSecondsSetValueFromMinutesSucceeds);
            RUN_TEST(MilliSecondsSetValueFromHoursSucceeds);
            RUN_TEST(MilliSecondsSetValueFromDaysSucceeds);

            // #include "test_ValueT.hpp"
            RUN_TEST(InitialisingValueTSucceeds);
            RUN_TEST(GetValueAsSameSucceeds);
            RUN_TEST(GetValueAsMicroSucceeds);
            RUN_TEST(SetValueAsSameSucceeds);
            RUN_TEST(SetValueAsMicroSucceeds);

            return UNITY_END();
        }

        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
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
