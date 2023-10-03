// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cmath>
#include <cstdint>
#include <stdio.h>
#include <compare>
#include <concepts>
#include <ratio>
#include <type_traits>

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
    
    /// @brief Class that holds a value of type TNumeric and supports conversion from and to std::ratio.
    /// Setting a value is supported by the copy assignment operator.
    /// Getting a value is supported by the indirection operator.
    /// Getting a scaled value (multiplied by its ratio) is supported by the functor operator.
    /// @tparam TNumeric A numeric type that holds the value.
    /// @tparam TRatio The scaling factor of the value.
    template<Numeric TNumeric = int, Ratio TRatio = std::ratio<1>>
    class ValueT
    {
        private:

            static constexpr auto ratio = (float) TRatio::num / TRatio::den;

            TNumeric value;

            template<Numeric TNumericOther, Ratio TRatioOther>
            friend class ValueT;

        public:

        /// @brief Default constructor.
        ValueT() = default;


        /// @brief Initialises ValueT with a numeric value.
        /// @tparam TNumericOther The type of the other value.
        /// @param other The other value.
        template<Numeric TNumericOther>
        ValueT(const TNumericOther other) noexcept
            : value(other) { }

        /// @brief Initialises ValueT with a scaled numeric value.
        /// @tparam TNumericOther The type of the other value.
        /// @tparam TRatioSrc The ratio of the other value.
        /// @param other The other value.
        template<Numeric TNumericSrc, Ratio TRatioSrc>
        ValueT(const ValueT<TNumericSrc, TRatioSrc>& other) noexcept
            : value(ConvertFrom(other)) { }

        /// @brief Assigns a value to the underlying data type.
        /// @param value The new value to set.
        /// @return A reference to this instance.
        ValueT<TNumeric, TRatio>& operator=(const TNumeric other) noexcept
        {
            value = other;

            return *this;
        }

        /// @brief Assigns a value to the underlying data type.
        /// @tparam TNumericSrc Type of other value.
        /// @tparam TRatioSrc Ratio of other value.
        /// @param other Object to assign from.
        /// @return A reference to this instance.
        template<Numeric TNumericSrc, Ratio TRatioSrc>
        ValueT<TNumeric, TRatio>& operator=(const ValueT<TNumericSrc, TRatioSrc>& other) noexcept
        {
            if constexpr (std::ratio_equal_v<TRatio, TRatioSrc>)
            {
                value = other.value;
                
                return *this;
            }
            else
            {
                using fromTRatioSrcToTRatio = std::ratio_multiply<TRatioSrc, std::ratio_divide<std::ratio<1>, TRatio>>;
                constexpr auto factor = (float) fromTRatioSrcToTRatio::num / fromTRatioSrcToTRatio::den;

                value = other.value * factor;
                
                return *this;
            }                
        }

        /// @brief Returns a copy of the value of the underlying data type.
        /// @return The value of the underlying data type.
        operator TNumeric() const noexcept 
        {
            return static_cast<TNumeric>(value);
        }

        /// @brief Returns a reference to the value of the underlying data type.
        /// @return The value of the underlying data type.
        const TNumeric& operator*() const noexcept
        {
            return value;
        }

        /// @brief Returns the value multiplied by its ratio of the underlying data type.
        /// @return The product of value and ratio.
        TNumeric operator()() const noexcept
        {
            return (TNumeric) value * ratio;
        }

        /// @brief 
        /// @tparam TNumericResult 
        /// @tparam TRatioResult 
        /// @return 
        template<Numeric TNumericResult = TNumeric, Ratio TRatioResult = std::ratio<1>>
        TNumericResult operator()() const noexcept
        {
            if constexpr (std::ratio_equal_v<TRatio, TRatioResult>)
            {
                return (TNumericResult) value;
            }
            else
            {
                using fromTRatioToTRatioResult = std::ratio_multiply<TRatio, std::ratio_divide<std::ratio<1>, TRatioResult>>;
                constexpr auto factor = (float) fromTRatioToTRatioResult::num / fromTRatioToTRatioResult::den;

                auto result = value * factor;
                return (TNumericResult) result;
            }
        }

        /// @brief Checks equality of this and other value.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns true, if value and other are equal; otherwise, false.
        template<Numeric TNumericOther>
        bool operator==(const TNumericOther other) const noexcept
        {
            return value == other;
        }

        /// @brief Checks equality of this and other value ignoring the ratio.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @tparam TRatioOther Ratio of underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns true, if value and other are equal; otherwise, false.
        template<Numeric TNumericOther, Ratio TRatioOther>
        bool operator==(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            static_assert(std::ratio_equal_v<TRatio, TRatioOther>, "Use operator<=> to compare values with different ratios.");
            
            return value == other.value;
        }

        /// @brief Checks equality of this and other value.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns false, if value and other are equal; otherwise, true;
        template<Numeric TNumericOther>
        bool operator!=(const TNumericOther other) const noexcept
        {
            return value != other;
        }

        /// @brief Checks equality of this and other value ignoring the ratio.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @tparam TRatioOther Ratio of underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns false, if value and other are equal; otherwise, true;
        template<Numeric TNumericOther, Ratio TRatioOther>
        bool operator!=(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            static_assert(std::ratio_equal_v<TRatio, TRatioOther>, "Use operator<=> to compare values with different ratios.");

            return !(value == other.value);
        }

        /// @brief Checks if this value is greater than other value.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns true, if value is greater than other; otherwise, false.
        template<Numeric TNumericOther>
        bool operator>(const TNumericOther other) const noexcept
        {
            return value > other;
        }

        /// @brief Checks if this value is greater than other value ignoring the ratio.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @tparam TRatioOther Ratio of underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns true, if value is greater than other; otherwise, false.
        template<Numeric TNumericOther, Ratio TRatioOther>
        bool operator>(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            static_assert(std::ratio_equal_v<TRatio, TRatioOther>, "Use operator<=> to compare values with different ratios.");

            return value > other.value;
        }

        /// @brief Checks if this value is greater or equal to than other value.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns true, if value is greater than or equal to other; otherwise, false.
        template<Numeric TNumericOther>
        bool operator>=(const TNumericOther other) const noexcept
        {
            return value >= other;
        }

        /// @brief Checks if this value is greater than or equal to other value ignoring the ratio.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @tparam TRatioOther Ratio of underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns true, if value is greater than or equal to other; otherwise, false.
        template<Numeric TNumericOther, Ratio TRatioOther>
        bool operator>=(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            static_assert(std::ratio_equal_v<TRatio, TRatioOther>, "Use operator<=> to compare values with different ratios.");

            return value >= other.value;
        }

        /// @brief Checks if this value is less than other value.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns true, if value is less than other; otherwise, false.
        template<Numeric TNumericOther>
        bool operator<(const TNumericOther other) const noexcept
        {
            return value < other;
        }

        /// @brief Checks if this value is less than other value ignoring the ratio.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @tparam TRatioOther Ratio of underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns true, if value is less than other; otherwise, false.
        template<Numeric TNumericOther, Ratio TRatioOther>
        bool operator<(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            static_assert(std::ratio_equal_v<TRatio, TRatioOther>, "Use operator<=> to compare values with different ratios.");

            return value < other.value;
        }

        /// @brief Checks if this value is less or equal to than other value.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns true, if value is less than or equal to other; otherwise, false.
        template<Numeric TNumericOther>
        bool operator<=(const TNumericOther other) const noexcept
        {
            return value <= other;
        }

        /// @brief Checks if this value is less than or equal to other value ignoring the ratio.
        /// @tparam TNumericOther Underlying data type of object to compare with.
        /// @tparam TRatioOther Ratio of underlying data type of object to compare with.
        /// @param other The value to compare with. 
        /// @return Returns true, if value is less than or equal to other; otherwise, false.
        template<Numeric TNumericOther, Ratio TRatioOther>
        bool operator<=(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            static_assert(std::ratio_equal_v<TRatio, TRatioOther>, "Use operator<=> to compare values with different ratios.");

            return value <= other.value;
        }

        // ISO C++ says that these are ambiguous, 
        // even though the worst conversion for the first is better 
        // than the worst conversion for the second:
        // /// @brief Adds other value to this and returns the sum.
        // /// @param value The addend.
        // /// @return Returns the result of the operation.
        // // ValueT<TNumeric, TRatio> operator+(const TNumeric value) const noexcept
        // ValueT<TNumeric, TRatio> operator+(const TNumeric value) const noexcept
        // {
        //     // ISO C++ says that these are ambiguous, even though the worst conversion for the first is better than the worst conversion for the second:
        //     ValueT<TNumeric, TRatio> result(this->value + value);
            
        //     return result;
        // }

        /// @brief Adds other value to this and returns the sum.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The addend.
        /// @return Returns the result of the operation.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio> operator+(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            if constexpr (std::ratio_equal_v<TRatio, TRatioOther>)
            {
                ValueT<TNumeric, TRatio> result(value + other.value);
                
                return result;
            }
            else
            {
                using fromTRatioOtherToTRatio = std::ratio_multiply<TRatioOther, std::ratio_divide<std::ratio<1>, TRatio>>;
                constexpr auto factor = (float) fromTRatioOtherToTRatio::num / fromTRatioOtherToTRatio::den;

                ValueT<TNumeric, TRatio> result(value + other.value * factor);
                
                return result;
            }
        }

        /// @brief Adds other value to this and assigns the sum to this.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @param other The addend.
        /// @return Returns the result of the operation assigned to the augend.
        template<Numeric TNumericOther>
        ValueT<TNumeric, TRatio>& operator+=(const TNumericOther other) noexcept
        {
            value += other;
            
            return *this;
        }

        /// @brief Adds other value to this and assigns the sum to this.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The addend.
        /// @return Returns the result of the operation assigned to the augend.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio>& operator+=(const ValueT<TNumericOther, TRatioOther>& other) noexcept
        {
            value = this->operator+(other);

            return *this;
        }

        /// @brief Substracts other value from this and returns the difference.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The subtrahend.
        /// @return Returns the result of the operation.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio> operator-(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            if constexpr (std::ratio_equal_v<TRatio, TRatioOther>)
            {
                ValueT<TNumeric, TRatio> result(value - other.value);
                
                return result;
            }
            else
            {
                using fromTRatioOtherToTRatio = std::ratio_multiply<TRatioOther, std::ratio_divide<std::ratio<1>, TRatio>>;
                constexpr auto factor = (float) fromTRatioOtherToTRatio::num / fromTRatioOtherToTRatio::den;

                ValueT<TNumeric, TRatio> result(value - other.value * factor);
                
                return result;
            }
        }

        /// @brief Substracts other value from this and assigns the difference to this.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @param other The subtrahend.
        /// @return Returns the result of the operation assigned to the minuend.
        template<Numeric TNumericOther>
        ValueT<TNumeric, TRatio>& operator-=(const TNumericOther other) noexcept
        {
            value -= other;
            
            return *this;
        }
        
        /// @brief Substracts other value from this and assigns the difference to this.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The subtrahend.
        /// @return Returns the result of the operation assigned to the minuend.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio>& operator-=(const ValueT<TNumericOther, TRatioOther>& other) noexcept
        {
            value = this->operator-(other);

            return *this;
        }

        /// @brief Multiplies other value with this and returns the difference.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The multiplier.
        /// @return Returns the result of the operation.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio> operator*(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            if constexpr (std::ratio_equal_v<TRatio, TRatioOther>)
            {
                ValueT<TNumeric, TRatio> result(value * other.value);
                
                return result;
            }
            else
            {
                using fromTRatioOtherToTRatio = std::ratio_multiply<TRatioOther, std::ratio_divide<std::ratio<1>, TRatio>>;
                constexpr auto factor = (float) fromTRatioOtherToTRatio::num / fromTRatioOtherToTRatio::den;

                ValueT<TNumeric, TRatio> result(value * other.value * factor);
                
                return result;
            }
        }

        /// @brief Multiplies other value with this and assigns the product to this.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @param other The multiplier.
        /// @return Returns the result of the operation assigned to the multiplicand.
        template<Numeric TNumericOther>
        ValueT<TNumeric, TRatio>& operator*=(const TNumericOther other) noexcept
        {
            value *= other;
            
            return *this;
        }

        /// @brief Multiplies other value with this and assigns the product to this.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The multiplier.
        /// @return Returns the result of the operation assigned to the multiplicand.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio>& operator*=(const ValueT<TNumericOther, TRatioOther>& other) noexcept
        {
            value = this->operator*(other);

            return *this;
        }

        /// @brief Divides this by other value and returns the quotient.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The divisor.
        /// @return Returns the result of the operation.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio> operator/(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            if constexpr (std::ratio_equal_v<TRatio, TRatioOther>)
            {
                ValueT<TNumeric, TRatio> result(value / other.value);
                
                return result;
            }
            else
            {
                using fromTRatioOtherToTRatio = std::ratio_multiply<TRatioOther, std::ratio_divide<std::ratio<1>, TRatio>>;
                constexpr auto factor = (float) fromTRatioOtherToTRatio::num / fromTRatioOtherToTRatio::den;

                ValueT<TNumeric, TRatio> result(value / (other.value * factor));
                
                return result;
            }
        }

        /// @brief Divides this by other value and assigns the quotient to this.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @param other The divisor.
        /// @return Returns the result of the operation assigned to the dividend.
        template<Numeric TNumericOther>
        ValueT<TNumeric, TRatio>& operator/=(const TNumericOther other) noexcept
        {
            value /= other;
            
            return *this;
        }

        /// @brief Divides this by other value and assigns the quotient to this.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The divisor.
        /// @return Returns the result of the operation assigned to the dividend.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio>& operator/=(const ValueT<TNumericOther, TRatioOther>& other) noexcept
        {
            value = this->operator/(other);

            return *this;
        }
        
        /// @brief Divides this by other value and returns the remainder.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @param other The divisor.
        /// @return Returns the result of the operation.
        template<Numeric TNumericOther>
        ValueT<TNumeric, TRatio> operator%(const TNumericOther other) const
        {
            static_assert(!std::is_same_v<TNumeric, long double>);

            // Only cast to int32_t/int64_t if one of the types is floating point.
            // | float  | float  | int32_t | int32_t |
            // | float  | double | int32_t | int64_t |
            // | float  | <int>  | int32_t | N/A     |
            // | double | float  | int64_t | int32_t |
            // | double | double | int64_t | int64_t |
            // | double | <int>  | int64_t | N/A     |
            // | <int>  | float  | N/A     | int32_t |
            // | <int>  | double | N/A     | int64_t |
            // | <int>  | <int>  | N/A     | N/A     |
            // This might look hard to read, but only with a complete if/else clause, 
            // we will not run into compile time error with floats/double on a modulo operation.
            if constexpr (std::is_same_v<TNumeric, float>)
            {
                if constexpr (std::is_same_v<TNumericOther, float>)
                {
                    ValueT<TNumeric, TRatio> result((int32_t) value % (int32_t) other);
                    
                    return result;
                }
                else if constexpr (std::is_same_v<TNumericOther, double>)
                {
                    ValueT<TNumeric, TRatio> result((int32_t) value % (int64_t) other);
                    
                    return result;
                }
                else
                {
                    ValueT<TNumeric, TRatio> result((int32_t) value % other);
                    
                    return result;
                }
            }
            else if constexpr (std::is_same_v<TNumeric, double>)
            {
                if constexpr (std::is_same_v<TNumericOther, float>)
                {
                    ValueT<TNumeric, TRatio> result((int64_t) value % (int32_t) other);
                    
                    return result;
                }
                else if constexpr (std::is_same_v<TNumericOther, double>)
                {
                    ValueT<TNumeric, TRatio> result((int64_t) value % (int64_t) other);
                    
                    return result;
                }
                else
                {
                    ValueT<TNumeric, TRatio> result((int64_t) value % other);
                    
                    return result;
                }                   
            }
            else
            {
                if constexpr (std::is_same_v<TNumericOther, float>)
                {
                    ValueT<TNumeric, TRatio> result(value % (int32_t) other);
                    
                    return result;
                }
                else if constexpr (std::is_same_v<TNumericOther, double>)
                {
                    ValueT<TNumeric, TRatio> result(value % (int64_t) other);
                    
                    return result;
                }
                else
                {
                    ValueT<TNumeric, TRatio> result(value % other);
                    
                    return result;
                }
            }
        }

        /// @brief Divides this by other value and returns the remainder.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The divisor.
        /// @return Returns the result of the operation.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio> operator%(const ValueT<TNumericOther, TRatioOther>& other) const
        {
            static_assert(!std::is_same_v<TNumeric, long double>);

            if constexpr (std::ratio_equal_v<TRatio, TRatioOther>)
            {
                // Only cast to int32_t/int64_t if one of the types is floating point.
                // | float  | float  | int32_t | int32_t |
                // | float  | double | int32_t | int64_t |
                // | float  | <int>  | int32_t | N/A     |
                // | double | float  | int64_t | int32_t |
                // | double | double | int64_t | int64_t |
                // | double | <int>  | int64_t | N/A     |
                // | <int>  | float  | N/A     | int32_t |
                // | <int>  | double | N/A     | int64_t |
                // | <int>  | <int>  | N/A     | N/A     |
                // This might look hard to read, but only with a complete if/else clause, 
                // we will not run into compile time error with floats/double on a modulo operation.
                if constexpr (std::is_same_v<TNumeric, float>)
                {
                    if constexpr (std::is_same_v<TNumericOther, float>)
                    {
                        ValueT<TNumeric, TRatio> result((int32_t) value % (int32_t) other.value);
                        
                        return result;
                    }
                    else if constexpr (std::is_same_v<TNumericOther, double>)
                    {
                        ValueT<TNumeric, TRatio> result((int32_t) value % (int64_t) other.value);
                        
                        return result;
                    }
                    else
                    {
                        ValueT<TNumeric, TRatio> result((int32_t) value % other.value);
                        
                        return result;
                    }
                }
                else if constexpr (std::is_same_v<TNumeric, double>)
                {
                    if constexpr (std::is_same_v<TNumericOther, float>)
                    {
                        ValueT<TNumeric, TRatio> result((int64_t) value % (int32_t) other.value);
                        
                        return result;
                    }
                    else if constexpr (std::is_same_v<TNumericOther, double>)
                    {
                        ValueT<TNumeric, TRatio> result((int64_t) value % (int64_t) other.value);
                        
                        return result;
                    }
                    else
                    {
                        ValueT<TNumeric, TRatio> result((int64_t) value % other.value);
                        
                        return result;
                    }                   
                }
                else
                {
                    if constexpr (std::is_same_v<TNumericOther, float>)
                    {
                        ValueT<TNumeric, TRatio> result(value % (int32_t) other.value);
                        
                        return result;
                    }
                    else if constexpr (std::is_same_v<TNumericOther, double>)
                    {
                        ValueT<TNumeric, TRatio> result(value % (int64_t) other.value);
                        
                        return result;
                    }
                    else
                    {
                        ValueT<TNumeric, TRatio> result(value % other.value);
                        
                        return result;
                    }
                }
            }
            else
            {
                using fromTRatioOtherToTRatio = std::ratio_multiply<TRatioOther, std::ratio_divide<std::ratio<1>, TRatio>>;
                constexpr auto factor = (float) fromTRatioOtherToTRatio::num / fromTRatioOtherToTRatio::den;

                // Only cast to int32_t/int64_t if one of the types is floating point.
                // | float  | float  | int32_t | int32_t |
                // | float  | double | int32_t | int64_t |
                // | float  | <int>  | int32_t | N/A     |
                // | double | float  | int64_t | int32_t |
                // | double | double | int64_t | int64_t |
                // | double | <int>  | int64_t | N/A     |
                // | <int>  | float  | N/A     | int32_t |
                // | <int>  | double | N/A     | int64_t |
                // | <int>  | <int>  | N/A     | N/A     |
                // This might look hard to read, but only with a complete if/else clause, 
                // we will not run into compile time error with floats/double on a modulo operation.
                if constexpr (std::is_same_v<TNumeric, float>)
                {
                    if constexpr (std::is_same_v<TNumericOther, float>)
                    {
                        ValueT<TNumeric, TRatio> result((int32_t) value % (int32_t) (other.value * factor));
                        
                        return result;
                    }
                    else if constexpr (std::is_same_v<TNumericOther, double>)
                    {
                        ValueT<TNumeric, TRatio> result((int32_t) value % (int64_t) (other.value * factor));
                        
                        return result;
                    }
                    else
                    {
                        ValueT<TNumeric, TRatio> result((int32_t) value % (other.value * factor));
                        
                        return result;
                    }
                }
                else if constexpr (std::is_same_v<TNumeric, double>)
                {
                    if constexpr (std::is_same_v<TNumericOther, float>)
                    {
                        ValueT<TNumeric, TRatio> result((int64_t) value % (int32_t) (other.value * factor));
                        
                        return result;
                    }
                    else if constexpr (std::is_same_v<TNumericOther, double>)
                    {
                        ValueT<TNumeric, TRatio> result((int64_t) value % (int64_t) (other.value * factor));
                        
                        return result;
                    }
                    else
                    {
                        ValueT<TNumeric, TRatio> result((int64_t) value % (other.value * factor));
                        
                        return result;
                    }                   
                }
                else
                {
                    if constexpr (std::is_same_v<TNumericOther, float>)
                    {
                        ValueT<TNumeric, TRatio> result(value % (int32_t) (other.value * factor));
                        
                        return result;
                    }
                    else if constexpr (std::is_same_v<TNumericOther, double>)
                    {
                        ValueT<TNumeric, TRatio> result(value % (int64_t) (other.value * factor));
                        
                        return result;
                    }
                    else
                    {
                        ValueT<TNumeric, TRatio> result(value % (other.value * factor));
                        
                        return result;
                    }
                }
            }
        }

        /// @brief Divides this by other value and assigns the remainder to this.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The divisor.
        /// @return Returns the result of the operation assigned to the dividend.
        template<Numeric TNumericOther>
        ValueT<TNumeric, TRatio>& operator%=(const TNumericOther other) noexcept
        {
            static_assert(!std::is_same_v<TNumeric, long double>);

            // Only cast to int32_t/int64_t if one of the types is floating point.
            // | float  | float  | int32_t | int32_t |
            // | float  | double | int32_t | int64_t |
            // | float  | <int>  | int32_t | N/A     |
            // | double | float  | int64_t | int32_t |
            // | double | double | int64_t | int64_t |
            // | double | <int>  | int64_t | N/A     |
            // | <int>  | float  | N/A     | int32_t |
            // | <int>  | double | N/A     | int64_t |
            // | <int>  | <int>  | N/A     | N/A     |
            // This might look hard to read, but only with a complete if/else clause, 
            // we will not run into compile time error with floats/double on a modulo operation.
            if constexpr (std::is_same_v<TNumeric, float>)
            {
                if constexpr (std::is_same_v<TNumericOther, float>)
                {
                    value = (int32_t) value % (int32_t) other.value;
                }
                else if constexpr (std::is_same_v<TNumericOther, double>)
                {
                    value = (int32_t) value % (int64_t) other.value;
                }
                else
                {
                    value = (int32_t) value % other.value;
                }
            }
            else if constexpr (std::is_same_v<TNumeric, double>)
            {
                if constexpr (std::is_same_v<TNumericOther, float>)
                {
                    value = (int64_t) value % (int32_t) other.value;
                }
                else if constexpr (std::is_same_v<TNumericOther, double>)
                {
                    value = (int64_t) value % (int64_t) other.value;
                }
                else
                {
                    value = (int64_t) value % other.value;
                }                   
            }
            else
            {
                if constexpr (std::is_same_v<TNumericOther, float>)
                {
                    value = value % (int32_t) other.value;
                }
                else if constexpr (std::is_same_v<TNumericOther, double>)
                {
                    value = value % (int64_t) other.value;
                }
                else
                {
                    value = value % other.value;
                }
            }

            return *this;
        }

        /// @brief Divides this by other value and assigns the remainder to this.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The divisor.
        /// @return Returns the result of the operation assigned to the dividend.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio>& operator%=(const ValueT<TNumericOther, TRatioOther>& other) noexcept
        {
            value = operator%(other);

            return *this;
        }

        /// @brief Compare this value with other value.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @param other The value to compare with. 
        /// @return If this is less than other, return less; if this is greater than other, return greater; otherwise returns equivalent (such 1'000'000 std::milli and 1 std::kilo).
        template<Numeric TNumericOther>
        std::weak_ordering operator<=>(const TNumeric other) const noexcept
        {
            return value <=> other;
        }

        /// @brief Determines the equivalence of this and other value up to a precision of 0.000001.
        /// @tparam TNumericOther A numeric type that holds the other value.
        /// @tparam TRatioOther The scaling factor of the other value.
        /// @param other The value to compare with. 
        /// @return If difference between this and scaled other is less than 0.000001, both are considered equivalent. If this is less than other, return less; if this is greater than other, return greater; otherwise returns equivalent (such 1'000'000 std::milli and 1 std::kilo).
        template<Numeric TNumericOther, Ratio TRatioOther>
        std::partial_ordering operator<=>(const ValueT<TNumericOther, TRatioOther>& other) const noexcept
        {
            if constexpr (std::ratio_equal_v<TRatio, TRatioOther>)
            {
                if(value < other) return std::partial_ordering::less;
                if(value > other) return std::partial_ordering::greater;
                return std::partial_ordering::equivalent;
            }
            else
            {
                static constexpr float precision = 0.000001;

                // We always multiply with the factor that is larger than 1 
                // as this seems to be more precise when dealing with float.
                using fromTRatioOtherToTRatio = std::ratio_multiply<TRatioOther, std::ratio_divide<std::ratio<1>, TRatio>>;
                constexpr auto factorToTRatio = (float) fromTRatioOtherToTRatio::num / fromTRatioOtherToTRatio::den;

                using fromTRatioToTRatioOther = std::ratio_multiply<TRatio, std::ratio_divide<std::ratio<1>, TRatioOther>>;
                constexpr auto factorToTRatioOther = (float) fromTRatioToTRatioOther::num / fromTRatioToTRatioOther::den;

                auto scaledValue = value * factorToTRatioOther;
                auto scaledOther = other.value * factorToTRatio;

                // Return equivlence if equal.
                if(value == scaledOther || other == scaledValue) return std::partial_ordering::equivalent;
                // Return equivalence if within precision (due to float uncertainty).
                if(value - scaledOther <= precision || other - scaledValue <= precision) return std::partial_ordering::equivalent;

                // Otherwise return depending on standard comparison.
                if constexpr (1 < factorToTRatio)
                {
                    return value <=> scaledOther;
                }
                else
                {
                    return scaledValue <=> other;
                }
            }
        }

        /// @brief Returns the underlying value.
        /// @return The underlying value.
        TNumeric GetValue()
        {
            return value;
        }

        /// @brief Returns the underlying value and converts it to TRatioDst.
        /// @tparam TRatioDst Destination ratio of value.
        /// @return The converted value.
        template<Ratio TRatioDst = std::ratio<1>>
        TNumeric GetValue() const
        {
            constexpr bool isEqual = std::ratio_equal_v<TRatio, TRatioDst>;
            if(isEqual) return value;

            using fromTRatioToTRatioDst = std::ratio_multiply<TRatio, std::ratio_divide<std::ratio<1>, TRatioDst>>;
            constexpr auto factor = (float) fromTRatioToTRatioDst::num / fromTRatioToTRatioDst::den;

            return value * factor;
        }

        /// @brief Sets the underlying value via conversion from TRatioSrc.
        /// @param value The new value to set.
        /// @return A reference to the called instance.
        ValueT<TNumeric, TRatio>& SetValue(const TNumeric value) noexcept
        {
            this->value = value;

            return *this;
        }

        /// @brief Sets the underlying value via conversion from TRatioSrc.
        /// @tparam TRatioSrc Source ratio of value.
        /// @param value The new value to set.
        /// @return A reference to the called instance.
        template<Ratio TRatioSrc = std::ratio<1>>
        ValueT& SetValue(TNumeric value)
        {
            if constexpr (std::ratio_equal_v<TRatio, TRatioSrc>)
            {
                this->value = value;

                return *this;
            }
            else
            {
                using fromTRatioSrcToTRatio = std::ratio_multiply<TRatioSrc, std::ratio_divide<std::ratio<1>, TRatio>>;
                constexpr auto factor = (float) fromTRatioSrcToTRatio::num / fromTRatioSrcToTRatio::den;

                this->value = value * factor;

                return *this;
            }
        }

        /// @brief Converts a ValueT from one ratio to another and assigns it to this.
        /// @tparam TNumericOther Type of other value.
        /// @tparam TRatioOther Ratio of other value.
        /// @param other Value to convert from.
        /// @return The converted value.
        template<Numeric TNumericOther, Ratio TRatioOther>
        ValueT<TNumeric, TRatio>& ConvertFrom(const ValueT<TNumericOther, TRatioOther>& other)
        {
            if constexpr (std::ratio_equal_v<TRatio, TRatioOther>)
            {
                value = other.value;
                
                return *this;
            }
            else
            {
                using fromTRatioOtherToTRatio = std::ratio_multiply<TRatioOther, std::ratio_divide<std::ratio<1>, TRatio>>;
                constexpr auto factor = (float) fromTRatioOtherToTRatio::num / fromTRatioOtherToTRatio::den;

                value = other.value * factor;
                
                return *this;
            }                
        }            

    };
}
