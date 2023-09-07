// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_Rs485.hpp"
#include "test_Validation.hpp"
#include "test_CellVoltage.hpp"
#include "test_BmsTemperature.hpp"
#include "test_Identifier.hpp"
#include "test_BatteryCurrent.hpp"
#include "test_BatteryChargeState.hpp"
#include "test_BatteryChargeTotal.hpp"

extern "C"
{
    namespace test::envNative::test_JkBms
    {
        using namespace JkBms;
        
        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        int runUnityTests()
        {
            UNITY_BEGIN();

            // #include "test_Rs485.hpp"
            RUN_TEST(CreatingInstanceFromVectorSucceeds);
            RUN_TEST(CreatingInstanceFromUniquePtrVectorSucceeds);
            RUN_TEST(AccessingDataWithInvalidIndexThrows);
            RUN_TEST(GettingLengthSucceeds);
            RUN_TEST(GettingDataSucceeds);
            RUN_TEST(InstantiatingMovesVectorMemory);

            // #include "test_Validation.hpp"
            RUN_TEST(IsValidSucceeds);
            RUN_TEST(IsValidFails);
            RUN_TEST(IsValidWithInvalidMinimumLengthFails);
            RUN_TEST(IsValidWithInvalidLengthFails);
            RUN_TEST(IsValidWithValidLengthSucceeds);
            RUN_TEST(IsValidWithInvalidChecksumFails);
            RUN_TEST(IsValidWithValidChecksumSucceeds);
            RUN_TEST(IsValidWithInvalidIdentifierFails);
            RUN_TEST(GettingMessagesSucceeds);
            RUN_TEST(GettingMultipleMessagesSucceeds);

            // #include "test_CellVoltage.hpp"
            RUN_TEST(TestingCellVoltageIdentifierSucceeds);
            RUN_TEST(TestingCellVoltageSucceeds);
            
            // #include "test_BmsTemperature.hpp"
            RUN_TEST(TestingBmsTemperatureIdentifierSucceeds);
            RUN_TEST(TestingBmsTemperatureWithInvalidMaximumThrows);
            RUN_TEST(TestingBmsTemperatureReturnsZero);
            RUN_TEST(TestingBmsTemperatureReturns100);
            RUN_TEST(TestingBmsTemperatureReturnsMinus1);
            RUN_TEST(TestingBmsTemperatureReturnsMinus40);
 
             // #include "test_Identifier.hpp"
            RUN_TEST(ValidatingNumberSucceeds);
            RUN_TEST(ValidatingIdentifierSucceeds);
            RUN_TEST(ValidatingIdentifierFails);
            
            // #include "test_BatteryCurrent.hpp"
            RUN_TEST(TestingCurrentDataIdentifierSucceeds);
            RUN_TEST(TestingCurrentDataReturnsPlus5);
            RUN_TEST(TestingCurrentDataReturnsPlus100Dot53);
            RUN_TEST(TestingCurrentDataReturnsZero);
            RUN_TEST(TestingCurrentDataReturnsMinus10);
            RUN_TEST(TestingCurrentDataReturnsMinus2Dot98);
            
            // #include "test_BatteryChargeState.hpp"
            RUN_TEST(TestingBatteryChargeStateIdentifierSucceeds);
            RUN_TEST(TestingBatteryChargeStateReturnsZero);
            RUN_TEST(BatteryChargeStateReturns32);
            RUN_TEST(BatteryChargeStateReturns100);
            RUN_TEST(BatteryChargeStateThrows);

            // #include "test_BatteryChargeTotal.hpp"
            RUN_TEST(BatteryChargeTotalIdentifierSucceeds);
            RUN_TEST(BatteryChargeTotalReturnsZero);
            RUN_TEST(SettingBatteryChargeTotalThrows);

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
