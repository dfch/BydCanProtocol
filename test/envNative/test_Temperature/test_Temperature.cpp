/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <tgmath.h>

#include "TemperatureUnit.h"
#include "Temperature.h"
#include "TemperatureKelvin.h"
#include "TemperatureCelsius.h"

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

        void GettingKelvinTemperatureSucceeds(void)
        {
            // Arrange
            auto expected = 345.67;
            Temperature::TemperatureKelvin sut(expected);

            // Act
            auto result = sut.GetValue();
            
            // Assert
            TEST_ASSERT_EQUAL_FLOAT(expected, result);
        }

        void SettingKelvinTemperatureSucceeds(void)
        {
            // Arrange
            auto expected = 345.67;
            Temperature::TemperatureKelvin sut;
            
            // Act
            sut.SetValue(expected);
            
            // Assert
            auto result = sut.GetValue();
            TEST_ASSERT_EQUAL_FLOAT(expected, result);
        }

        void SettingNegativeKelvinTemperatureThrows(void)
        {
            // Arrange
            Temperature::TemperatureKelvin sut;
            
            // Act
            auto hasThrown = false;
            try
            {
                sut.SetValue(-1);
            }
            catch(const std::exception& e)
            {
                hasThrown = true;
            }
            
            // Assert
            TEST_ASSERT_TRUE(hasThrown);
        }

        void GettingCelsiusTemperatureSucceeds(void)
        {
            // Arrange
            auto expected = 23.45;
            Temperature::TemperatureCelsius sut(expected);

            // Act
            auto result = sut.GetValue();
            
            // Assert
            TEST_ASSERT_EQUAL_FLOAT(expected, result);
        }

        void SettingCelsiusTemperatureSucceeds(void)
        {
            // Arrange
            auto expected = 23.45;
            Temperature::TemperatureCelsius sut;
            
            // Act
            sut.SetValue(expected);
            
            // Assert
            auto result = sut.GetValue();
            TEST_ASSERT_EQUAL_FLOAT(expected, result);
        }

        void ConvertingFromCelsiusToKelvinSucceeds()
        {
            // Arrange
            auto celsius = 23.45;
            auto expected = celsius + 273.15;
            Temperature::TemperatureCelsius sut(celsius);

            // Act
            auto result = static_cast<Temperature::TemperatureKelvin>(sut).GetValue();
            
            // Assert
            TEST_ASSERT_EQUAL_FLOAT(expected, result);
        }

        typedef union tagUinteger16
        {
            std::uint16_t Uinteger16;
            std::byte Bytes[2];
        } Uinteger16;

        void ConvertingFromCelsiusToKelvin2Succeeds()
        {
            // Arrange
            auto celsius = 14.3;
            auto expected = celsius + 273.15;
            Temperature::TemperatureCelsius sut(celsius);

            // Act
            auto k = static_cast<Temperature::TemperatureKelvin>(sut).GetValue();
            TEST_ASSERT_EQUAL_FLOAT(expected, k);

            Uinteger16 result;
            result.Uinteger16 = (std::uint16_t) roundf(k);
            
            // Assert
            TEST_ASSERT_EQUAL_HEX8(0x1F, result.Bytes[0]);
            TEST_ASSERT_EQUAL_HEX8(0x01, result.Bytes[1]);
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
