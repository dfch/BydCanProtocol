// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <string>

#include <StringExtensions.h>

namespace test::envNative::test_StringExtensions
{
    void StringTrimWhitespaceSucceeds()
    {
        auto const expected = std::string("ArbitraryString WithLeadingAndTrailingSpaces");
        auto const leading = std::string("\t "); 
        auto const trailing = std::string("   \n"); 
        std::string const sut = leading + expected + trailing;

        // Test struct.
        auto result = StringExtensions::Trim(sut);
        TEST_ASSERT_EQUAL_STRING(expected.c_str(), result.c_str());

        // Test operator.
        result = sut << StringExtensions::Trim;
        TEST_ASSERT_EQUAL_STRING(expected.c_str(), result.c_str());
    }

    void StringTrimCharSucceeds()
    {
        auto const expected = std::string("ArbitraryString WithLeadingAndTrailingTrimChars");
        auto const leading = std::string("tt"); 
        auto const trailing = std::string("ttt"); 
        std::string const sut = leading + expected + trailing;

        // Test struct.
        auto result = StringExtensions::Trim(sut, (const char) 't');
        TEST_ASSERT_EQUAL_STRING(expected.c_str(), result.c_str());
    }

    void StringToLowerSucceeds()
    {
        auto const expected = std::string("lowercasestring");
        std::string const sut = std::string("LowerCaseString");

        // Test struct.
        auto result = StringExtensions::ToLowerCase(sut);
        TEST_ASSERT_EQUAL_STRING(expected.c_str(), result.c_str());

        // Test operator.
        auto result2 = sut << StringExtensions::ToLowerCase;
        TEST_ASSERT_EQUAL_STRING(expected.c_str(), result2.c_str());
    }

    void StringToUpperSucceeds()
    {
        auto const expected = std::string("UPPERCASESTRING");
        std::string const sut = std::string("UpperCaseString");

        // Test struct.
        auto result = StringExtensions::ToUpperCase(sut);
        TEST_ASSERT_EQUAL_STRING(expected.c_str(), result.c_str());

        // Test operator.
        auto result2 = sut << StringExtensions::ToUpperCase;
        TEST_ASSERT_EQUAL_STRING(expected.c_str(), result2.c_str());
    }
} 
