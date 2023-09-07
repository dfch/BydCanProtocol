// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <Contract.h>
#include <Word.h>
#include <Volt.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;
    using namespace Units;

    #pragma pack(push, 1)
    /// @brief Represents a voltage of the BMS.
    /// @param TMin Specifies the minimum size of the underlying value.
    /// @param TMax Specifies the maximum size of the underlying value.
    /// @param TSize Specifies the scaling factor to apply.
    template<size_t TMin, size_t TMax, typename TScale>
    struct tagSecondsBase
    {
        static_assert(std::is_enum_v<TScale>, "TScale must be an enum type.");

        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded voltage.
        Word Value;

        /// @brief Converts the underlying value to Volt.
        /// @return The converted Volt.
        Volt ToVolt() const 
        {
            auto scaled = Value.ToLittleEndian();
            Contract::Expects([scaled] { return TMin <= scaled && TMax >= scaled; }, NAMEOF(ToVolt));

            Volt result(scaled, TScale);

            return result;
        }

        /// @brief Sets a voltage to a value.
        /// @param value The value to set.
        void FromVolt(Volt value)
        {
            auto scaled = value.Value.ScaleTo(TScale);

            Contract::Expects([value] { return TMin <= scaled && TMax >= scaled; }, NAMEOF(FromVolt));

            Value.Value = scaled;
        }
    };
    #pragma pack(pop)
}
