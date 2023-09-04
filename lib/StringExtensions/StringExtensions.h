// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <string>

namespace StringExtensions
{
    struct StdStringTrim_t
    {
        std::string operator()(const std::string& value) const;
        std::string operator()(const std::string& value, const char trimChar) const;
    };

    const StdStringTrim_t Trim = {};

    std::string operator<<(const std::string& value, StdStringTrim_t func);

    struct StdStringToLower_t
    {
        std::string operator()(const std::string& value) const;
    };

    const StdStringToLower_t ToLowerCase = {};

    std::string operator<<(const std::string& value, StdStringToLower_t func);

    struct StrStringToUpper_t
    {
        std::string operator()(const std::string& value) const;
    };

    const StrStringToUpper_t ToUpperCase = {};

    std::string operator<<(const std::string& value, StrStringToUpper_t func);
}
