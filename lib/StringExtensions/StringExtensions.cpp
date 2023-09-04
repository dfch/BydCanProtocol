// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include "StringExtensions.h"

#include <algorithm>

std::string StringExtensions::StdStringTrim_t::operator()(const std::string &value) const
{
    // Not efficient, but it works.
    constexpr char trimChar[] = { ' ', '\t', '\n', '\r' };

    auto result = std::string(value);
    size_t previousLength;
    do
    {
        previousLength = result.length();

        for(auto c : trimChar)
        {
            result = operator()(std::string(result), c);
        }
    } while (result.length() != previousLength);
    

    return result;
}

std::string StringExtensions::StdStringTrim_t::operator()(const std::string &value, const char trimChar) const
{
    std::size_t start = value.find_first_not_of(trimChar);
    std::size_t end = value.find_last_not_of(trimChar);

    auto result = start == end ? std::string() : value.substr(start, end - start + 1);

    return result;
}

std::string StringExtensions::operator<<(const std::string &value, StdStringTrim_t func)
{
    return func(value);
}

std::string StringExtensions::StdStringToLower_t::operator()(const std::string &value) const
{
    std::string result;

    std::transform(value.begin(), value.end(), result.begin(), ::tolower);

    return result;
}

std::string StringExtensions::operator<<(const std::string &value, StdStringToLower_t func)
{
    return func(value);
}

std::string StringExtensions::StrStringToUpper_t::operator()(const std::string &value) const
{
    std::string result;

    std::transform(value.begin(), value.end(), result.begin(), ::toupper);

    return result;
}

std::string StringExtensions::operator<<(const std::string &value, StrStringToUpper_t func)
{
    return func(value);
}

