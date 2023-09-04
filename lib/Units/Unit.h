// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "Value.h"

namespace Units
{
    /// @brief Represents a unit.
    class Unit
    {
        public:
            /// @brief Represents the value of the unit.
            Units::Value Value;

            /// @brief Creates an instance of Unit and initialises the value to 0.
            Unit();

            /// @brief Creates an instance of Unit with the specified value.
            Unit(float value);

            /// @brief Creates an instance of Unit with the specified value. The specified value is assumed to have a scaling factor applied as specified by tag.
            Unit(float value, Scale tag);
    };
}
