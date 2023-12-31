// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include "Unit.h"

namespace Units
{
    Unit::Unit()
        : Value(0)
    {
        // N/A
    }

    Unit::Unit(float value)
        : Value(value)
    {
        // N/A
    }

    Unit::Unit(float value, Scale tag)
        : Value(value, tag)
    {
        // N/A
    }
}
