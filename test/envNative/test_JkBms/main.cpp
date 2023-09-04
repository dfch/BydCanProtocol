// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_Rs485.hpp"
#include "test_Validation.hpp"
#include "test_CellVoltage.hpp"
#include "test_PowerManagementTemperature.hpp"
#include "test_Identifier.hpp"

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
            RUN_TEST(GettingFramesSucceeds);

            // #include "test_CellVoltage.hpp"
            RUN_TEST(TestingCellVoltageIdentifierSucceeds);
            RUN_TEST(TestingCellVoltageSucceeds);
            
            // #include "test_PowerManagementTemperature.hpp"
            RUN_TEST(TestingPowerManagementTemperatureIdentifierSucceeds);
            RUN_TEST(TestingPowerManagementTemperatureWithInvalidMaximumThrows);
            RUN_TEST(TestingPowerManagementTemperatureReturnsZero);
            RUN_TEST(TestingPowerManagementTemperatureReturns100);
            RUN_TEST(TestingPowerManagementTemperatureReturnsMinus1);
            RUN_TEST(TestingPowerManagementTemperatureReturnsMinus40);
            
            // #include "test_Identifier.hpp"
            RUN_TEST(ValdiatingNumberSucceeds);
            RUN_TEST(ValdiatingIdentifierSucceeds);
            RUN_TEST(ValdiatingIdentifierFails);
            
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
