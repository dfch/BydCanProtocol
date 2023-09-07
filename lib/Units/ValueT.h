// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <ratio>
#include <concepts>

namespace Units
{
    /// @brief A template requiring std::ratio<> as its type parameter.
    template<typename T>
    concept Ratio = requires
    {
        { T::num } -> std::convertible_to<const intmax_t>;
        { T::den } -> std::convertible_to<const intmax_t>;
    };

    /// @brief A template requiring a numeric type as its type parameter.
    template<typename T>
    concept Numeric = 
        std::is_arithmetic_v<T> &&
        !std::is_same_v<T, bool>;
    
    using DefaultRatio = std::ratio<1>;

    /// @brief Class that holds a value of type TNumeric and supports conversion from and to std::ratio.
    /// @tparam TNumeric A numeric type that holds the value.
    /// @tparam TRatio The scaling factor of the value.
    template<Numeric TNumeric = int, Ratio TRatio = DefaultRatio>
    class ValueT
    {
        private:

        TNumeric value;

        public:

        /// @brief Default constructor.
        ValueT() = default;

        /// @brief Constructor that initialises the instance to value scaled as TRatio.
        /// @param value The initial value of the instance.
        ValueT(TNumeric value)
            : value(value) { }
        
        /// @brief Constructor that initialises the instance to value and converts it to TRatio.
        /// @tparam TRatioSrc Scale of value.
        /// @param value The initial value of the instance.
        template<Ratio TRatioSrc>
        ValueT(TNumeric value)
            : value(SetValue<TRatioSrc>(value)) { }

        /// @brief Returns the underlying value.
        /// @return The underlying value.
        TNumeric GetValue()
        {
            return value;
        }

        /// @brief Returns the underlying value and converts it to TRatioDst.
        /// @tparam TRatioDst Destination ratio of value.
        /// @return The converted value.
        template<Ratio TRatioDst = DefaultRatio>
        TNumeric GetValue() const
        {
            constexpr bool isEqual = std::ratio_equal<TRatio, TRatioDst>::value;
            if(isEqual) return value;

            using ratio = std::ratio_multiply<TRatio, std::ratio_divide<DefaultRatio, TRatioDst>>;
            constexpr auto factor = (float) ratio::num / ratio::den;

            return value * factor;
        }

        /// @brief Sets the underlying value via conversion from TRatioSrc.
        /// @param value The new value to set.
        /// @return A reference to the called instance.
        ValueT& SetValue(TNumeric value)
        {
            this->value = value;

            return *this;
        }

        /// @brief Sets the underlying value via conversion from TRatioSrc.
        /// @tparam TRatioSrc Source ratio of value.
        /// @param value The new value to set.
        /// @return A reference to the called instance.
        template<Ratio TRatioSrc = DefaultRatio>
        ValueT& SetValue(TNumeric value)
        {
            constexpr bool isEqual = std::ratio_equal<TRatio, TRatioSrc>::value;
            if(isEqual)
            {
                this->value = value;

                return *this;
            }

            using ratio = std::ratio_multiply<TRatioSrc, std::ratio_divide<DefaultRatio, TRatio>>;
            constexpr auto factor = (float) ratio::num / ratio::den;

            this->value = value * factor;

            return *this;
        }
    };
}
