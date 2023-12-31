// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <Rs485.h>
#include <Frame.h>
#include <Qword.h>

namespace test::envNative::test_JkBms
{
    using namespace JkBms;
    
    void ValidatingNumberSucceeds()
    {
        #pragma pack(push, 1)
        struct tagArbitraryStruct
        {
            uint8_t Number;
            Id Id;
        };
        #pragma pack(pop)
        
        std::vector<std::uint8_t> data 
        { 
            0x42,
            0x79,
        };

        auto sut = reinterpret_cast<const tagArbitraryStruct*>(data.data());

        TEST_ASSERT_EQUAL_UINT8(0x42, sut->Number);
    }

    void ValidatingIdentifierSucceeds()
    {
        #pragma pack(push, 1)
        struct tagArbitraryStruct
        {
            uint8_t Number;
            Identifier Identifier;
        };
        #pragma pack(pop)
        
        std::vector<std::uint8_t> data 
        { 
            0x42,
            0x79,
        };

        auto sut = reinterpret_cast<const tagArbitraryStruct*>(data.data());

        auto result = sut->Identifier.IsValid();

        TEST_ASSERT_TRUE(result);
        TEST_ASSERT_EQUAL(Id::CellVoltage, sut->Identifier.Value);
    }

    void ValidatingIdentifierFails()
    {
        #pragma pack(push, 1)
        struct tagArbitraryStruct
        {
            uint8_t Number;
            Identifier Identifier;
        };
        #pragma pack(pop)
        
        std::vector<std::uint8_t> data 
        { 
            0x42,
            0xCC,
        };

        auto sut = reinterpret_cast<const tagArbitraryStruct*>(data.data());

        auto result = sut->Identifier.IsValid();

        TEST_ASSERT_FALSE(result);
        TEST_ASSERT_NOT_EQUAL(Id::CellVoltage, sut->Identifier.Value);
    }
}
