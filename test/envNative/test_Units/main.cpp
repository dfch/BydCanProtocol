// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_Units.hpp"
#include "test_ValueT.hpp"
#include "test_Second.hpp"
#include "test_Millisecond.hpp"
#include "test_Microsecond.hpp"
#include "test_AmpereHour.hpp"
#include "test_Sla.hpp"

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
            
            // #include "test_ValueT.hpp"
            RUN_TEST(InitialisingValueTSucceeds);
            RUN_TEST(InitialisingValueTWithValueTSucceeds);
            RUN_TEST(InitialisingValueTInstantiatesScaled);
            RUN_TEST(InitialisingValueTTruncates);
            RUN_TEST(AssigningValueTSucceeds);
            RUN_TEST(AssigningValueTScaledSucceeds);
            RUN_TEST(AssigningValueTTruncates1);
            RUN_TEST(AssigningValueTTruncates2);
            RUN_TEST(ConvertsFromSucceeds);
            RUN_TEST(GetValueAsSameSucceeds);
            RUN_TEST(GetValueAsMicroSucceeds);
            RUN_TEST(SetValueAsSameSucceeds);
            RUN_TEST(SetValueAsMicroSucceeds);
            RUN_TEST(OperatorEqualNumericReturnsTrue);
            RUN_TEST(OperatorEqualNumericReturnsFalse);
            RUN_TEST(OperatorEqualReturnsTrue);
            RUN_TEST(OperatorNotEqualNumericReturnsTrue);
            RUN_TEST(OperatorNotEqualNumericReturnsFalse);
            RUN_TEST(OperatorNotEqualReturnsTrue);
            RUN_TEST(OperatorNotEqualReturnsFalse);
            RUN_TEST(OperatorLessReturnsTrue);
            RUN_TEST(OperatorLessReturnsTrue2);
            RUN_TEST(OperatorLessNumericReturnsTrue);
            RUN_TEST(OperatorLessReturnsFalse);
            RUN_TEST(OperatorLessReturnsFalse2);
            RUN_TEST(OperatorLessOrEqualReturnsTrue);
            RUN_TEST(OperatorLessOrEqualReturnsTrue2);
            RUN_TEST(OperatorLessOrEqualReturnsFalse);
            RUN_TEST(OperatorGreaterReturnsTrue);
            RUN_TEST(OperatorGreaterReturnsFalse);
            RUN_TEST(OperatorGreaterReturnsFalse2);
            RUN_TEST(OperatorGreaterOrEqualReturnsTrue);
            RUN_TEST(OperatorGreaterOrEqualReturnsTrue2);
            RUN_TEST(OperatorGreaterOrEqualReturnsFalse);
            RUN_TEST(OperatorSpaceshipReturnsEquivalent);
            RUN_TEST(OperatorSpaceshipReturnsEquivalent2);
            RUN_TEST(OperatorSpaceshipReturnsEquivalent3);
            RUN_TEST(OperatorSpaceshipReturnsEquivalent4);
            RUN_TEST(OperatorSpaceshipReturnsEquivalent5);
            RUN_TEST(OperatorSpaceshipReturnsEquivalent6);
            RUN_TEST(OperatorSpaceshipReturnsEquivalent7);
            RUN_TEST(OperatorSpaceshipReturnsLess);
            RUN_TEST(AddingValuetSucceeds);
            RUN_TEST(AddingValuetFloatingPointSucceeds);
            RUN_TEST(AddingValuetFloatingPointTruncates);
            RUN_TEST(SubstractingValuetSucceeds);
            RUN_TEST(SubstractingValuetFloatingPointSucceeds);
            RUN_TEST(SubstractingValuetFloatingPointTruncates);
            RUN_TEST(SubstractingAndAssigningValuetSucceeds);
            RUN_TEST(SubstractingAndAssigningValuetOverflows);
            RUN_TEST(DividingValueTSucceeds);
            RUN_TEST(DividingValueTFpSucceeds);
            RUN_TEST(DividingValueTTruncates);
            RUN_TEST(DividingValueTScaledSucceeds);
            RUN_TEST(DividingAndAssigningValueTScaledSucceeds);
            RUN_TEST(ModuloValuetSucceeds);
            RUN_TEST(ModuloValuetFloatFloatSucceeds);
            RUN_TEST(ModuloValuetFloatDoubleSucceeds);
            RUN_TEST(ModuloValuetFloatIntSucceeds);
            RUN_TEST(ModuloValuetDoubleFloatSucceeds);
            RUN_TEST(ModuloValuetDoubleDoubleSucceeds);
            RUN_TEST(ModuloValuetDoubleIntSucceeds);
            RUN_TEST(ModuloValuetIntFloatSucceeds);
            RUN_TEST(ModuloValuetIntDoubleSucceeds);
            RUN_TEST(ModuloValuetIntIntSucceeds);
            RUN_TEST(ModuloAndAssigningValuetSucceeds);
            RUN_TEST(ModuloAndAssigningValuetFloatFloatSucceeds);
            RUN_TEST(ModuloAndAssigningValuetFloatDoubleSucceeds);
            RUN_TEST(ModuloAndAssigningValuetFloatIntSucceeds);
            RUN_TEST(ModuloAndAssigningValuetDoubleFloatSucceeds);
            RUN_TEST(ModuloAndAssigningValuetDoubleDoubleSucceeds);
            RUN_TEST(ModuloAndAssigningValuetDoubleIntSucceeds);
            RUN_TEST(ModuloAndAssigningValuetIntFloatSucceeds);
            RUN_TEST(ModuloAndAssigningValuetIntDoubleSucceeds);
            RUN_TEST(ModuloAndAssigningValuetIntIntSucceeds);
            RUN_TEST(ModuloAndAssigningValuetIntDoubleScaledSucceeds);
            RUN_TEST(FunctorFloaUint32ReturnsScaledValue);
            RUN_TEST(FunctorUint32DecaReturnsScaledValue);
            RUN_TEST(FunctorUint32DeciReturnsInteger);
            RUN_TEST(FunctorUint32NegativeReturnsZero);
            RUN_TEST(FunctorFloatReturnsScaledValue);
            RUN_TEST(FunctorFloatDecaReturnsScaledValue);
            RUN_TEST(FunctorReturnsDifferentType1);
            RUN_TEST(FunctorReturnsDifferentType2);
            RUN_TEST(FunctorReturnsDifferentType3);
            RUN_TEST(FunctorReturnsDifferentType4);
            RUN_TEST(DereferenceAndCastOperatorAreNotTheSame);
            RUN_TEST(ImplicitCastSucceeds);
            RUN_TEST(ExplicitCastSucceeds);
            RUN_TEST(AssignWithDifferentRatioSucceeds1);
            RUN_TEST(AssignWithDifferentRatioSucceeds2);

            // #include "test_Second.hpp"
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

            // #include "test_Microsecond.hpp"
            RUN_TEST(ScaleToSecondsReturns42);
            RUN_TEST(ScaleToSecondsReturnsM42);
            RUN_TEST(ScaleToMillisecondsReturns1500);
            RUN_TEST(ScaleToMillisecondsReturnsM1500);
            RUN_TEST(ScaleToHoursReturns3);
            RUN_TEST(ScaleToMinutesReturns210);
            RUN_TEST(SetValueWithRatioReturns1500000);

            // #include "test_AmpereHour.hpp"
            // RUN_TEST(TestAmpereHour2);
            
            // #include "test_Sla.hpp"
            RUN_TEST(AllocatingDiskSpaceSucceeds);

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
