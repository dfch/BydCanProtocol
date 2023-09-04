// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#if defined(ESP_PLATFORM)

#include <unity.h>

#include <Can.h>
#include <Configuration.h>

using CanTwai::Can;
using CanTwai::Configuration;

extern "C"
{
    namespace test::envEmbedded::test_CanTwai
    {
        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        void InstantiatingSucceeds()
        {
            // Arrange
            twai_general_config_t general = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_21, GPIO_NUM_22, TWAI_MODE_NORMAL);
            twai_timing_config_t timing = TWAI_TIMING_CONFIG_500KBITS();
            twai_filter_config_t filter = TWAI_FILTER_CONFIG_ACCEPT_ALL();

            // Act
            auto sut = Can::Factory::Create(&general, &timing, &filter);

            // Assert
            TEST_ASSERT_NOT_NULL(sut);

            // Cleanup
            auto stopped = twai_stop();
            TEST_ASSERT_EQUAL(ESP_OK, stopped);
            auto uninstalled = twai_driver_uninstall();
            TEST_ASSERT_EQUAL(ESP_OK, uninstalled);
        }

        void InstantiatingViaConfigurationSucceeds()
        {
            // Arrange
            auto configuration = std::make_shared<Configuration>();

            // Act
            auto sut = Can::Factory::Create(configuration);

            // Assert
            TEST_ASSERT_NOT_NULL(sut);

            // Cleanup
            auto stopped = twai_stop();
            TEST_ASSERT_EQUAL(ESP_OK, stopped);
            auto uninstalled = twai_driver_uninstall();
            TEST_ASSERT_EQUAL(ESP_OK, uninstalled);
        }

        void SendingMessageReturnsTrue()
        {
            // Arrange
            auto expected = true;
            auto configuration = std::make_shared<Configuration>(GPIO_NUM_17, GPIO_NUM_16, TWAI_MODE_NORMAL, 500);
            auto sut = Can::Factory::Create(configuration);

            // Act
            auto result = sut->Send();

            // Assert
            TEST_ASSERT_EQUAL(expected, result);

            // Cleanup
            auto stopped = twai_stop();
            TEST_ASSERT_EQUAL(ESP_OK, stopped);
            auto uninstalled = twai_driver_uninstall();
            TEST_ASSERT_EQUAL(ESP_OK, uninstalled);
        }

        int runUnityTests(void)
        {
            UNITY_BEGIN();

            RUN_TEST(InstantiatingSucceeds);
            RUN_TEST(InstantiatingViaConfigurationSucceeds);
            RUN_TEST(SendingMessageReturnsTrue);

            return UNITY_END();
        }

        void app_main() 
        {
            runUnityTests();
        }
    }
}

#endif
