/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <cstdint>

#include <Percent.h>
#include <AmpereHour.h>

namespace Victron
{
    /// @brief Represents the battery state information.
    class StateInfo
    {
        public:
            /// @brief Represents the state of charge.
            Units::Percent StateOfCharge;
            /// @brief Represents the state of health.
            Units::Percent StateOfHealth;
            /// @brief Represents the total size of the battery bank in Ampere hours.
            Units::AmpereHour SizeTotalAmpereHour;
            /// @brief Represents the available size of the battery bank in Ampere hours.
            Units::AmpereHour SizeAvailableAmpereHour;

    };
}
