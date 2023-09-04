// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <optional>
#include <stdexcept>

namespace Expected
{
    /// @brief Simple version of expected similar to C++23 without all the functionality. 
    /// Can story an expected value and an unexpected value. Uses std::optional internally.
    /// @tparam T The execpted value.
    /// @tparam E The unexecpted value.
    template<typename T, typename E>
    class expected : public std::optional<T>
    {
        private:
            std::optional<E> unexpected;

        public:
            constexpr explicit expected() noexcept
                : std::optional<T>() { }

            constexpr expected( const expected& other)
                : unexpected(other.unexpected), std::optional<T>(other) { }

            constexpr expected( expected&& other) noexcept
                : unexpected(other.unexpected), std::optional<T>(other) { }

            constexpr explicit expected(T& value)
                : std::optional<T>(value) { }

            constexpr explicit expected(E& value)
                : unexpected(value) { }

            constexpr explicit expected(const E& value) noexcept
                : unexpected(value) { }

            using std::optional<T>::operator=;

            expected& operator=(const E& other) noexcept
            {
                unexpected = other;

                this->reset();

                return *this;
            }

            E error() const 
            {
                if(std::optional<T>::has_value()) throw std::logic_error("error(): true == expected::has_value()");

                return unexpected.value(); 
            }
    };
}
