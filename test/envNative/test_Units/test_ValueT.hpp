// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>
#include <ratio>

#include "Value.h"

namespace test::envNative::test_Units
{
    using namespace Units;

    void InitialisingValueTSucceeds()
    {
        ValueT<int, std::milli> sut (1'500);

        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL(1'500, result);
    }

    void InitialisingValueTWithValueTSucceeds()
    {
        ValueT<int, std::milli> other(3'500'000);
        ValueT<float, std::kilo> sut (other);

        TEST_ASSERT_EQUAL_FLOAT(3.5, sut);
    }

    void InitialisingValueTInstantiatesScaled()
    {
        ValueT<float, std::milli> other (3'500);
        ValueT sut (other);

        TEST_ASSERT_EQUAL_FLOAT(3'500, sut);
    }

    void InitialisingValueTTruncates()
    {
        ValueT sut (3.5);

        TEST_ASSERT_EQUAL_FLOAT(3, sut);
    }

    void AssigningValueTSucceeds()
    {
        ValueT<float> other (3.5);
        ValueT<float> sut = other;

        TEST_ASSERT_EQUAL_FLOAT(3.5, sut);
    }

    void AssigningValueTScaledSucceeds()
    {
        ValueT<int, std::milli> other (4'000'000);

        TEST_ASSERT_EQUAL(4'000'000, other);
        TEST_ASSERT_EQUAL(4'000'000, *other);
        TEST_ASSERT_EQUAL(4'000, other());

        ValueT<float, std::kilo> sut;
        sut = other;

        TEST_ASSERT_EQUAL_FLOAT(4.0, sut);
    }

    void AssigningValueTTruncates1()
    {
        ValueT<float, std::milli> other (3'500);
        ValueT<> sut = other;

        TEST_ASSERT_EQUAL_FLOAT(3, sut);
    }

    void AssigningValueTTruncates2()
    {
        ValueT<float, std::milli> other (3'500);
        ValueT<int> sut = other;

        TEST_ASSERT_EQUAL_FLOAT(3, sut);
    }

    void ConvertsFromSucceeds()
    {
        ValueT<int, std::milli> other(2'123'456);

        ValueT<uint8_t, std::kilo> sut;

        sut.ConvertFrom(other);

        TEST_ASSERT_EQUAL_UINT8(2, sut);
    }

    void GetValueAsSameSucceeds()
    {
        ValueT<int, std::milli> sut (1'500);

        auto result = sut.GetValue<std::milli>();

        TEST_ASSERT_EQUAL(1'500, result);
    }

    void GetValueAsMicroSucceeds()
    {
        ValueT<int, std::milli> sut (1'500);

        auto result = sut.GetValue<std::micro>();

        TEST_ASSERT_EQUAL(1'500'000, result);
    }

    void SetValueAsSameSucceeds()
    {
        ValueT<int, std::milli> sut;

        sut.SetValue<std::milli>(1'500);
        
        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL(1'500, result);
    }

    void SetValueAsMicroSucceeds()
    {
        ValueT<float, std::milli> sut;

        sut.SetValue<std::micro>(1'500'000);
        
        auto result = sut.GetValue();

        TEST_ASSERT_EQUAL(1'500, result);
    }

    void OperatorEqualNumericReturnsTrue()
    {
        int32_t other (3'500);
        ValueT<uint32_t, std::milli> sut (3'500);

        auto result = sut.operator==(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorEqualNumericReturnsFalse()
    {
        int32_t other (3'500);
        ValueT<uint32_t, std::kilo> sut (3'499);

        auto result = sut.operator==(other);

        TEST_ASSERT_FALSE(result);
    }

    void OperatorEqualReturnsTrue()
    {
        ValueT<int32_t, std::milli> other (3'500);
        ValueT<uint32_t, std::milli> sut (3'500);

        auto result = sut.operator==(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorNotEqualNumericReturnsTrue()
    {
        int32_t other (3'500);
        ValueT<uint32_t, std::milli> sut (3'499);

        auto result = sut.operator!=(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorNotEqualNumericReturnsFalse()
    {
        int32_t other (3'500);
        ValueT<uint32_t, std::kilo> sut (3'500);

        auto result = sut.operator!=(other);

        TEST_ASSERT_FALSE(result);
    }

    void OperatorNotEqualReturnsTrue()
    {
        ValueT<int32_t, std::kilo> other (3'500);
        ValueT<uint32_t, std::kilo> sut (3'499);

        auto result = sut.operator!=(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorNotEqualReturnsFalse()
    {
        ValueT<uint32_t, std::milli> other (3'500);
        ValueT<uint32_t, std::milli> sut (3'500);

        auto result = sut.operator!=(other);

        TEST_ASSERT_FALSE(result);
    }

    void OperatorLessNumericReturnsTrue()
    {
        float other (42.0);
        ValueT sut (5);

        auto result = sut.operator<(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorLessReturnsTrue()
    {
        ValueT other (42);
        ValueT sut (5);

        auto result = sut.operator<(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorLessReturnsTrue2()
    {
        ValueT<float> other (42.0);
        ValueT sut (5);

        auto result = sut.operator<(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorLessReturnsFalse()
    {
        ValueT other (42);
        ValueT sut (42);

        auto result = sut.operator<(other);

        TEST_ASSERT_FALSE(result);
    }

    void OperatorLessReturnsFalse2()
    {
        ValueT other (5);
        ValueT sut (42);

        auto result = sut.operator<(other);

        TEST_ASSERT_FALSE(result);
    }

    void OperatorLessOrEqualReturnsTrue()
    {
        ValueT other (42);
        ValueT sut (5);

        auto result = sut.operator<=(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorLessOrEqualReturnsTrue2()
    {
        ValueT other (42);
        ValueT sut (42);

        auto result = sut.operator<=(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorLessOrEqualReturnsFalse()
    {
        ValueT other (5);
        ValueT sut (42);

        auto result = sut.operator<=(other);

        TEST_ASSERT_FALSE(result);
    }

    void OperatorGreaterReturnsTrue()
    {
        ValueT other (5);
        ValueT sut (42);

        auto result = sut.operator>(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorGreaterReturnsFalse()
    {
        ValueT other (42);
        ValueT sut (42);

        auto result = sut.operator>(other);

        TEST_ASSERT_FALSE(result);
    }

    void OperatorGreaterReturnsFalse2()
    {
        ValueT other (42);
        ValueT sut (5);

        auto result = sut.operator>(other);

        TEST_ASSERT_FALSE(result);
    }

    void OperatorGreaterOrEqualReturnsTrue()
    {
        ValueT other (5);
        ValueT sut (42);

        auto result = sut.operator>=(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorGreaterOrEqualReturnsTrue2()
    {
        ValueT other (42);
        ValueT sut (42);

        auto result = sut.operator>=(other);

        TEST_ASSERT_TRUE(result);
    }

    void OperatorGreaterOrEqualReturnsFalse()
    {
        ValueT other (42);
        ValueT sut (5);

        auto result = sut.operator>=(other);

        TEST_ASSERT_FALSE(result);
    }

    void OperatorSpaceshipReturnsEquivalent()
    {
        ValueT<float, std::milli> other (5'000);
        ValueT sut (5);

        auto result = sut.operator<=>(other);

        TEST_ASSERT_TRUE(std::partial_ordering::equivalent == result);
    }

    void OperatorSpaceshipReturnsEquivalent2()
    {
        ValueT<float, std::milli> other (-55'000'000);
        ValueT<int8_t, std::kilo> sut (-55);

        auto result = sut.operator<=>(other);

        TEST_ASSERT_TRUE(std::partial_ordering::equivalent == result);
    }

    void OperatorSpaceshipReturnsEquivalent3()
    {
        ValueT<int32_t, std::milli> other (-5'500'000);
        ValueT<float, std::kilo> sut (-5.5);

        auto result = sut.operator<=>(other);

        TEST_ASSERT_TRUE(std::partial_ordering::equivalent == result);
    }

    void OperatorSpaceshipReturnsEquivalent4()
    {
        ValueT<uint8_t, std::deci> other (42);
        ValueT<float> sut (4.2);

        auto result = sut.operator<=>(other);

        TEST_ASSERT_TRUE(std::partial_ordering::equivalent == result);
    }

    void OperatorSpaceshipReturnsEquivalent5()
    {
        ValueT<float> other (4.2);
        ValueT<uint8_t, std::deci> sut (42);

        auto result = sut.operator<=>(other);

        TEST_ASSERT_TRUE(std::partial_ordering::equivalent == result);
    }

    void OperatorSpaceshipReturnsEquivalent6()
    {
        ValueT<float> other (3.14159);
        ValueT<float, std::deci> sut (31.4159);

        auto result = sut.operator<=>(other);

        TEST_ASSERT_TRUE(std::partial_ordering::equivalent == result);
    }

    void OperatorSpaceshipReturnsEquivalent7()
    {
        ValueT<float> other (31.4159);
        ValueT<float, std::deca> sut (3.14159);

        auto result = sut.operator<=>(other);

        TEST_ASSERT_TRUE(std::partial_ordering::equivalent == result);
    }

    void OperatorSpaceshipReturnsLess()
    {
        ValueT<uint64_t, std::micro> other (5'000'100);
        ValueT<float, std::kilo> sut (5);

        auto result = sut.operator<=>(other);

        TEST_ASSERT_TRUE(std::partial_ordering::equivalent == result);
        TEST_ASSERT_TRUE(std::partial_ordering::less == result);
        TEST_ASSERT_TRUE(std::partial_ordering::greater == result);
    }

    void AddingValuetSucceeds()
    {
        ValueT sut (42);
        ValueT other(5);

        auto result = sut + other;

        TEST_ASSERT_EQUAL(47, result);
    }

    void AddingValuetFloatingPointSucceeds()
    {
        ValueT<float> sut (42.5);
        ValueT other(5);

        auto result = sut + other;

        TEST_ASSERT_EQUAL_FLOAT(47.5, result);
    }

    void AddingValuetFloatingPointTruncates()
    {
        ValueT sut (42);
        ValueT<float> other(5.7);

        auto result = sut + other;

        TEST_ASSERT_EQUAL_FLOAT(47, result);
    }

    void SubstractingValuetSucceeds()
    {
        ValueT sut (5);
        ValueT other(42);

        auto result = sut - other;

        TEST_ASSERT_EQUAL(-37, result);
    }

    void SubstractingValuetFloatingPointSucceeds()
    {
        ValueT<float> sut (42.5);
        ValueT other(5);

        auto result = sut - other;

        TEST_ASSERT_EQUAL_FLOAT(37.5, result);
    }

    void SubstractingValuetFloatingPointTruncates()
    {
        ValueT sut (42);
        ValueT<float> other(5.3);

        auto result = sut - other;

        TEST_ASSERT_EQUAL_FLOAT(36, result);
    }

    void SubstractingAndAssigningValuetSucceeds()
    {
        ValueT other (5);
        ValueT sut (42);

        sut -= other;

        TEST_ASSERT_EQUAL(37, sut);
    }

    void SubstractingAndAssigningValuetOverflows()
    {
        ValueT<uint32_t> other (42);
        ValueT<uint32_t> sut (5);

        sut -= other;

        TEST_ASSERT_EQUAL(4294967259, *sut);
    }

    void DividingValueTSucceeds()
    {
        ValueT sut (42);
        ValueT other (7);
        
        auto result = sut / other;

        TEST_ASSERT_EQUAL(6, result);
    }

    void DividingValueTFpSucceeds()
    {
        ValueT sut (42);
        ValueT<float> other (3.5);
        
        auto result = sut / other;

        TEST_ASSERT_EQUAL_FLOAT(12, result);
    }

    void DividingValueTTruncates()
    {
        ValueT sut (42);
        ValueT other (5);
        
        auto result = sut / other;

        TEST_ASSERT_EQUAL(8, result);
    }

    void DividingValueTScaledSucceeds()
    {
        ValueT<float> sut (42);
        ValueT<int, std::milli> other (7'000);
        
        auto result = sut / other;

        TEST_ASSERT_EQUAL_FLOAT(6, result);
    }

    void DividingAndAssigningValueTScaledSucceeds()
    {
        ValueT<float> sut (42);
        ValueT<int, std::milli> other (7'000);
        
        sut /= other;

        TEST_ASSERT_EQUAL_FLOAT(6, sut);
    }

    void ModuloValuetSucceeds()
    {
        ValueT sut (42);
        ValueT other (5);

        auto result = sut % other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, result);
    }

    void ModuloValuetFloatFloatSucceeds()
    {
        ValueT<float> sut (42);
        ValueT<float> other (5);

        auto result = sut % other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, result);
    }

    void ModuloValuetFloatDoubleSucceeds()
    {
        ValueT<float> sut (42);
        ValueT<double> other (5);

        auto result = sut % other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, result);
    }

    void ModuloValuetFloatIntSucceeds()
    {
        ValueT<float> sut (42);
        ValueT<int> other (5);

        auto result = sut % other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, result);
    }

    void ModuloValuetDoubleFloatSucceeds()
    {
        ValueT<double> sut (42);
        ValueT<float> other (5);

        auto result = sut % other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, result);
    }

    void ModuloValuetDoubleDoubleSucceeds()
    {
        ValueT<double> sut (42);
        ValueT<double> other (5);

        auto result = sut % other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, result);
    }

    void ModuloValuetDoubleIntSucceeds()
    {
        ValueT<double> sut (42);
        ValueT<int> other (5);

        auto result = sut % other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, result);
    }

    void ModuloValuetIntFloatSucceeds()
    {
        ValueT<int> sut (42);
        ValueT<float> other (5);

        auto result = sut % other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, result);
    }

    void ModuloValuetIntDoubleSucceeds()
    {
        ValueT<int> sut (42);
        ValueT<double> other (5);

        auto result = sut % other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, result);
    }

    void ModuloValuetIntIntSucceeds()
    {
        ValueT<int> sut (42);
        ValueT<int> other (5);

        auto result = sut % other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, result);
    }

    void ModuloAndAssigningValuetSucceeds()
    {
        ValueT sut (42);
        ValueT other (5);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void ModuloAndAssigningValuetFloatFloatSucceeds()
    {
        ValueT<float> sut (42);
        ValueT<float> other (5);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void ModuloAndAssigningValuetFloatDoubleSucceeds()
    {
        ValueT<float> sut (42);
        ValueT<double> other (5);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void ModuloAndAssigningValuetFloatIntSucceeds()
    {
        ValueT<float> sut (42);
        ValueT<int> other (5);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void ModuloAndAssigningValuetDoubleFloatSucceeds()
    {
        ValueT<double> sut (42);
        ValueT<float> other (5);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void ModuloAndAssigningValuetDoubleDoubleSucceeds()
    {
        ValueT<double> sut (42);
        ValueT<double> other (5);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void ModuloAndAssigningValuetDoubleIntSucceeds()
    {
        ValueT<double> sut (42);
        ValueT<int> other (5);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void ModuloAndAssigningValuetIntFloatSucceeds()
    {
        ValueT<int> sut (42);
        ValueT<float> other (5);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void ModuloAndAssigningValuetIntDoubleSucceeds()
    {
        ValueT<int> sut (42);
        ValueT<double> other (5);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void ModuloAndAssigningValuetIntIntSucceeds()
    {
        ValueT<int> sut (42);
        ValueT<int> other (5);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void ModuloAndAssigningValuetIntDoubleScaledSucceeds()
    {
        ValueT<int> sut (42);
        ValueT<double, std::milli> other (5'000);

        sut %= other;
        
        TEST_ASSERT_EQUAL_FLOAT(2, sut);
    }

    void FunctorFloaUint32ReturnsScaledValue()
    {
        ValueT<uint32_t> sut (42);

        auto result = sut ();

        TEST_ASSERT_EQUAL_FLOAT(42, result);
    }

    void FunctorUint32DecaReturnsScaledValue()
    {
        ValueT<uint32_t, std::deca> sut (42);

        auto result = sut ();

        TEST_ASSERT_EQUAL_FLOAT(420, result);
    }

    void FunctorUint32DeciReturnsInteger()
    {
        ValueT<uint32_t, std::deci> sut (42);

        auto result = sut ();

        TEST_ASSERT_EQUAL_FLOAT(4, result);
    }

    void FunctorUint32NegativeReturnsZero()
    {
        ValueT<uint32_t> sut (5);
        sut -= 42;

        auto result = sut();

        TEST_ASSERT_EQUAL_FLOAT(0, result);
    }

    void FunctorFloatReturnsScaledValue()
    {
        ValueT<float> sut (42);

        auto result = sut();

        TEST_ASSERT_EQUAL_FLOAT(42, result);
    }

    void FunctorFloatDecaReturnsScaledValue()
    {
        ValueT<float, std::deca> sut (42);

        auto result = sut();

        TEST_ASSERT_EQUAL_FLOAT(420, result);
    }

    void FunctorReturnsDifferentType1()
    {
        ValueT<float, std::milli> sut (42'000'000);

        auto result = sut.operator()<float, std::kilo>();

        TEST_ASSERT_EQUAL(42, result);
    }

    void FunctorReturnsDifferentType2()
    {
        ValueT<uint32_t, std::milli> sut (42);

        auto result = sut.operator()<float>();

        TEST_ASSERT_EQUAL_FLOAT(0.042, result);
    }

    void FunctorReturnsDifferentType3()
    {
        ValueT<uint8_t, std::kilo> sut (42);

        auto result = sut.operator()<float, std::milli>();

        TEST_ASSERT_EQUAL_FLOAT(42'000'000, result);
    }

    void FunctorReturnsDifferentType4()
    {
        ValueT<uint32_t, std::milli> sut (42'000'000);

        int32_t result = sut.operator()<uint8_t, std::kilo>();

        TEST_ASSERT_EQUAL(42, result);
    }

    void DereferenceAndCastOperatorAreNotTheSame()
    {
        ValueT<uint8_t, std::kilo> sut (42);

        auto result = (uint8_t) sut;
        TEST_ASSERT_EQUAL(result, 42);

        auto reference = *sut;
        TEST_ASSERT_EQUAL(reference, 42);

        TEST_ASSERT_EQUAL(result, reference);

        result++;
        TEST_ASSERT_NOT_EQUAL(result, reference);
        // ? check if this works, or if we have to cast explicitly
        TEST_ASSERT_EQUAL_UINT8(sut, reference);
    }

    void ImplicitCastSucceeds()
    {
        ValueT<uint8_t, std::kilo> sut (42);

        uint8_t result = sut;
        TEST_ASSERT_EQUAL(42, sut);
    }

    void ExplicitCastSucceeds()
    {
        ValueT<uint8_t, std::kilo> sut (42);

        auto result = (uint8_t) sut;
        TEST_ASSERT_EQUAL(42, sut);
    }

    void AssignWithDifferentRatioSucceeds1()
    {
        ValueT<uint32_t> sut (42);

        ValueT<float, std::milli> other(2000);

        sut = other;

        auto result = *sut;

        TEST_ASSERT_EQUAL(2, result);
    }

    void AssignWithDifferentRatioSucceeds2()
    {
        using MilliVolt = ValueT<uint16_t, std::milli>;
        using CentiVolt = ValueT<uint16_t, std::ratio<10, 1000>>;

        MilliVolt sut (42);

        CentiVolt other(150);

        sut = other;

        auto resultFloat = sut.operator()<float, std::ratio<1>>();
        auto result = *sut;

        TEST_ASSERT_EQUAL(1'500, result);

        sut += 42;
        TEST_ASSERT_EQUAL(1'542, *sut);

        sut += other;
        TEST_ASSERT_EQUAL(3'042, *sut);

        sut = 42;

        sut = sut + other;
        TEST_ASSERT_EQUAL(1'542, *sut);

        sut = 42;
        sut = sut + CentiVolt(1);
        TEST_ASSERT_EQUAL(52, *sut);

        sut = 42;
        sut += MilliVolt(1);
        TEST_ASSERT_EQUAL(43, *sut);

        sut = 42;
        sut += CentiVolt(1);
        TEST_ASSERT_EQUAL(52, *sut);

        auto resultMilliVolt = MilliVolt(42) + CentiVolt(1);
        TEST_ASSERT_EQUAL(52, *resultMilliVolt);

        sut = 1;
        sut = sut + MilliVolt(42);
        TEST_ASSERT_EQUAL(43, *sut);

        using Volt = ValueT<int16_t>;
        using MilliVoltInt16 = ValueT<int16_t, std::milli>;
        using CentiVoltFloat = ValueT<float, std::ratio<10, 1000>>;
        using MilliVoltFloat = ValueT<float, std::milli>;

        Volt v(1);
        MilliVoltInt16 mv(1);
        CentiVoltFloat cv(100);

        auto opPlus = mv + cv;
        TEST_ASSERT_EQUAL(1001, opPlus.GetValue());

        auto opMinus = mv - cv;
        TEST_ASSERT_EQUAL(-999, opMinus);

        MilliVoltFloat mvf(100);
        auto opPlusSame = mv + mvf;
        TEST_ASSERT_EQUAL(101, opPlusSame.GetValue());
    }
}