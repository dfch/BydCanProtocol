// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include "Identifier.h"
#include "AmpereBase.h"
#include "Scale.h"

namespace JkBms::Identifiers
{
    /// @brief Represents the Charge Over Current Protection (A) of the BMS.
    using ChargeOverCurrentProtection = tagAmpereBase<1, 1000, Scale::Default>;
}
