// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_BydCan.hpp"

extern "C"
{
    namespace test::envNative::test_Byd
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

            RUN_TEST(CreateSucceeds);
            RUN_TEST(CreateDvccSucceeds);
            RUN_TEST(CreateStateInfoSucceeds);
            RUN_TEST(CreateAlarmWarningSucceeds);
            RUN_TEST(CreateEventsUnusedSucceeds);
            RUN_TEST(CreateBatteryInfoSucceeds);
            RUN_TEST(CreateUnknown0Succeeds);
            RUN_TEST(CreateHistorySucceeds);
            RUN_TEST(CreateBatterySizeSucceeds);
            RUN_TEST(CreateBankInfoSucceeds);
            RUN_TEST(CreateCellInfoSucceeds);
            RUN_TEST(CreateBatteryStatsSucceeds);
            RUN_TEST(CreateManufacturerInfoSucceeds);
            RUN_TEST(CreateProductInfoSucceeds);
            RUN_TEST(SerialiseDataSucceeds);
            RUN_TEST(DataCopyToSmallerSucceeds);
            RUN_TEST(DataCopyToEqualSucceeds);
            RUN_TEST(DataCopyToLargerNoinitSucceeds);
            RUN_TEST(DataCopyToLargerInitSucceeds);

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
