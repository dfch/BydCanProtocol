/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <bitset>

#include "AlarmFlags.h"
#include "WarningFlags.h"

namespace Victron
{
    /// @brief Represents the alarm and warning flags.
    typedef struct alarmWarning
    {
        /// @brief Represents the alarm flags.
        std::bitset<32> Alarm;

        /// @brief Represents the warning flags.
        std::bitset<32> Warning;

        /// @brief Resets all alarm and warning flags.
        void Reset();

        /// @brief Gets a value indicating whether any alarm flag is set.
        /// @return True, if any alarm flag is set; false, otherwise.
        bool HasAlarm();
        /// @brief Gets a value indicating whether any warning flag is set.
        /// @return True, if any warning flag is set; false, otherwise.
        bool HasWarning();
        /// @brief Gets a value indicating whether any alarm or warning flag is set.
        /// @return True, if any alarm or warning flag is set; false, otherwise.
        bool HasAlarmOrWarning();

        /// @brief Gets a value indicating whether the specified alarm flag is set.
        /// @param flag The alarm flag to check.
        /// @return True, if the specified alarm flag is set; false, otherwise.
        bool HasAlarm(AlarmFlags flag);
        /// @brief Sets the specified alarm flag.
        /// @param flag The alarm flag to set.
        /// @return True, if the previous value of the specified alarm flag was set; false, otherwise.
        bool SetAlarm(AlarmFlags flag);
        /// @brief Resets the specified alarm flag.
        /// @param flag The alarm flag to reset.
        /// @return True, if the previous value of the specified alarm flag was set; false, otherwise.
        bool ResetAlarm(AlarmFlags flag);
        /// @brief Resets all alarm flags.
        void ResetAlarm();

        /// @brief Gets a value indicating whether the specified warning flag is set.
        /// @param flag The warning flag to check.
        /// @return True, if the specified warning flag is set; false, otherwise.
        bool HasWarning(WarningFlags flag);
        /// @brief Sets the specified warning flag.
        /// @param flag The warning flag to set.
        /// @return True, if the previous value of the specified warning flag was set; false, otherwise.
        bool SetWarning(WarningFlags flag);
        /// @brief Resets the specified warning flag.
        /// @param flag The warning flag to reset.
        /// @return True, if the previous value of the specified warning flag was set; false, otherwise.
        bool ResetWarning(WarningFlags flag);
        /// @brief Resets all warning flags.
        void ResetWarning();
        
    } AlarmWarning;
}
