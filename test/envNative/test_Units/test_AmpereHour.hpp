// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>
#include <ratio>
#include <concepts>
#include <optional>

#include <Contract.h>
#include <ValueT.h>
#include <Word.h>

namespace test::envNative::test_Units
{
    using namespace Endian;
    using namespace Units;

    /// @brief A template requiring std::ratio<> as its type parameter.
    template<typename T>
    concept Ratio = requires
    {
        { T::num } -> std::convertible_to<const intmax_t>;
        { T::den } -> std::convertible_to<const intmax_t>;
    };

    /// @brief A template requiring std::ratio<> as its type parameter.
    template<typename TValue, size_t TMin, size_t TMax, Ratio TRatio>
    struct tagSettingIdentifier
    {
        /// @brief The encoded Ampere.
        Word Value;

        tagSettingIdentifier() = default;

        tagSettingIdentifier(Word value)
        {
            auto v = Value.ToLittleEndian();

            Contract::Expects([v] { return TMin <= v && TMax >= v; }, NAMEOF(.ctor));

            this->SetValue(v);
        }

        tagSettingIdentifier(TValue value)
            : tagSettingIdentifier::tagSettingIdentifier((Word) value.GetValue()) { }

        template<Ratio TRatioDst = std::ratio<1>>
        TValue ToUnit() const
        {
            auto v = Value.ToLittleEndian();

            Contract::Expects([v] { return TMin <= v && TMax >= v; }, NAMEOF(ToUnit));
            
            TValue result;
            result.template SetValue<TRatioDst>(v);

            return result;
        }

        template<Ratio TRatioSrc = std::ratio<1>>
        void SetValue(TValue value)
        {
            auto v = value.template GetValue<TRatioSrc>();

            Contract::Expects([v] { return TMin <= v && TMax >= v; }, NAMEOF(ToUnit));

            this->SetValue(v);
        }

    };

    using MilliVolt2 = ValueT<uint16_t, std::milli>;

    using CellVoltageProtection2 = tagSettingIdentifier<MilliVolt2, 0, 4'500, std::milli>;
    
    void TestAmpereHour2()
    {
        TEST_PASS();
        MilliVolt2 mv(1'500);
        CellVoltageProtection2 sut(mv);

        MilliVolt2 mv2(1'900);
        sut.SetValue(mv2);


        auto result = sut.template ToUnit().GetValue();
        TEST_ASSERT_EQUAL_UINT16(42, result);
        // sut.Value.ToLittleEndian
        // TEST_FAIL_MESSAGE("Not yet implemented.");
    }

    template<typename T>
    concept OptionalCallable = requires 
    {
        typename T::value_type;
        requires std::invocable<typename T::value_type>;
    };

    template<typename TSrc, typename TDst, OptionalCallable TFunc>
    struct tagTypeInfo
    {

    };
}
