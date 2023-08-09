/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include "AlarmWarning.h"

namespace Victron
{
    void AlarmWarning::Reset()
    {
        Alarm = {0};
        Warning = {0};
    }

    bool AlarmWarning::HasAlarm()
    {
        return Alarm.any();
    }

    bool AlarmWarning::HasWarning()
    {
        return Warning.any();
    }

    bool AlarmWarning::HasAlarmOrWarning()
    {
        return HasAlarm() || HasWarning();
    }

    bool AlarmWarning::HasAlarm(AlarmFlags flag)
    {
        auto result = Alarm.test(flag);

        return result;
    }

    bool AlarmWarning::SetAlarm(AlarmFlags flag)
    {
        auto result = HasAlarm(flag);

        Alarm.set(flag);

        return result;
    }

    bool AlarmWarning::ResetAlarm(AlarmFlags flag)
    {
        auto result = HasAlarm(flag);

        Alarm.set(flag, false);

        return result;
    }

    void AlarmWarning::ResetAlarm()
    {
        Alarm.reset();
    }

    bool AlarmWarning::HasWarning(WarningFlags flag)
    {
        auto result = Warning.test(flag);

        return result; 
    }

    bool AlarmWarning::SetWarning(WarningFlags flag)
    {
        auto result = HasWarning(flag);

        Warning.set(flag);

        return result;
    }

    bool AlarmWarning::ResetWarning(WarningFlags flag)
    {
        auto result = HasWarning(flag);

        Warning.set(flag, false);

        return result;
    }

    void AlarmWarning::ResetWarning()
    {
        Warning.reset();
    }
}
