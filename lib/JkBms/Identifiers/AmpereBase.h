// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>

#include <Contract.h>
#include <Word.h>
#include <Ampere.h>

#include "Identifier.h"

namespace JkBms::Identifiers
{
    using namespace JkBms;
    using namespace Endian;
    using namespace Units;

    #pragma pack(push, 1)
    /// @brief Represents a current (A) of the BMS.
    /// @param TMin Specifies the minimum size of the underlying value.
    /// @param TMax Specifies the maximum size of the underlying value.
    /// @param TSize Specifies the scaling factor to apply.
    template<size_t TMin, size_t TMax, typename TScale>
    struct tagAmpereBase
    {
        static_assert(std::is_enum_v<TScale>, "TScale must be an enum type.");

        /// @brief BMS settings identifier.
        JkBms::Identifier Identifier;

        /// @brief The encoded Ampere.
        Word Value;

        /// @brief Converts the underlying value to Ampere. 
        /// @return The converted Ampere.
        Ampere ToAmpere() const 
        {
            auto scaled = Value.ToLittleEndian();

            Contract::Expects([scaled] { return TMin <= scaled && TMax >= scaled; }, NAMEOF(ToAmpere));

            Ampere result(scaled, TScale);

            return result;
        }

        /// @brief Sets the underlying value.
        /// @param value The value to set.
        void FromAmpere(Ampere value)
        {
            auto scaled = value.Value.ScaleTo(TScale);

            Contract::Expects([value] { return TMin <= scaled && TMax >= scaled; }, NAMEOF(FromAmpere));

            Value.Value = scaled;
        }
    };
    #pragma pack(pop)
}
