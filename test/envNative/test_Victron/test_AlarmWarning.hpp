// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <AlarmWarning.h>

namespace test::envNative::test_Victron
{
    using Victron::AlarmWarning;
    
    void ResetAllSucceeds()
    {
        // Arrange
        AlarmWarning sut;

        // Act
        sut.Reset();

        // Assert
        auto result = sut.Alarm.any() || sut.Warning.any();
        TEST_ASSERT_FALSE(result);
    }

    void ResetAlarmsSucceeds()
    {
        // Arrange
        AlarmWarning sut;

        // Act
        sut.ResetAlarm();

        // Assert
        auto result = sut.Alarm.any();
        TEST_ASSERT_FALSE(result);
    }

    void InitAlarmSucceeds()
    {
        // Arrange
        // Act
        AlarmWarning sut
        { 
            .Alarm = 1 << Victron::HighTemperatureAlarm
        };

        // Assert
        auto result = sut.Alarm.test(Victron::HighTemperatureAlarm);
        TEST_ASSERT_TRUE_MESSAGE(result, sut.Alarm.to_string().c_str());
    }

    void SetAlarmSucceeds()
    {
        // Arrange
        AlarmWarning sut;

        // Act
        sut.SetAlarm(Victron::LowBatteryVoltageAlarm);

        // Assert
        auto result = sut.Alarm.test(Victron::LowBatteryVoltageAlarm);
        TEST_ASSERT_TRUE_MESSAGE(result, sut.Alarm.to_string().c_str());
    }

    void ResetAlarmSucceeds()
    {
        // Arrange
        AlarmWarning sut
        { 
            .Alarm = Victron::CellImbalanceAlarm
        };

        // Act
        sut.ResetAlarm(Victron::CellImbalanceAlarm);

        // Assert
        auto result = sut.Alarm.test(Victron::CellImbalanceAlarm);
        TEST_ASSERT_FALSE(result);
    }

    void ResetWarningsSucceeds()
    {
        // Arrange
        AlarmWarning sut;

        // Act
        sut.ResetWarning();

        // Assert
        auto result = sut.Warning.any();
        TEST_ASSERT_FALSE(result);
    }

    void InitWarningSucceeds()
    {
        // Arrange
        // Act
        AlarmWarning sut
        { 
            .Warning = 1 << Victron::LowChargeTemperatureWarning
        };
        
        // Assert
        auto result = sut.Warning.test(Victron::LowChargeTemperatureWarning);
        TEST_ASSERT_TRUE_MESSAGE(result, sut.Warning.to_string().c_str());
    }

    void SetWarningSucceeds()
    {
        // Arrange
        AlarmWarning sut;

        // Act
        sut.SetWarning(Victron::InternalFailureWarning);

        // Assert
        auto result = sut.Warning.test(Victron::InternalFailureWarning);
        TEST_ASSERT_TRUE_MESSAGE(result, sut.Warning.to_string().c_str());
    }
    
    void ResetWarningSucceeds()
    {
        // Arrange
        AlarmWarning sut
        { 
            .Warning = Victron::HighChargeCurrentWarning
        };

        // Act
        sut.ResetWarning(Victron::HighChargeCurrentWarning);

        // Assert
        auto result = sut.Warning.test(Victron::HighChargeCurrentWarning);
        TEST_ASSERT_FALSE(result);
    }
}
