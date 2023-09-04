// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <Contract.h>

namespace test::envNative::test_Contract
{
    using namespace Contract;

    class ArbitraryClass
    {
        public:
            bool ThrowsOnTrue(bool flag)
            {
                Ensures([flag] { return !flag; }, ErrorCode::InvalidArgument);

                return !flag;
            }

            bool ThrowsOnTrueWithDefaultArgument(bool flag)
            {
                Ensures([flag] { return !flag; });

                return !flag;
            }

    };

    void EnsuresDoesNotThrow()
    {
        ArbitraryClass sut;

        auto result = sut.ThrowsOnTrue(false);

        TEST_ASSERT_TRUE(result);
    }

    void EnsuresDoesThrow()
    {
        ArbitraryClass sut;

        auto hasThrown = false;
        try
        {
            auto result = sut.ThrowsOnTrue(true);
        }
        catch(const std::exception& e)
        {
            hasThrown = true;
        }

        TEST_ASSERT_TRUE(hasThrown);
    }

    void EnsuresDoesThrowWithDefaultArgument()
    {
        ArbitraryClass sut;

        auto hasThrown = false;
        try
        {
            auto result = sut.ThrowsOnTrueWithDefaultArgument(true);
        }
        catch(const std::exception& e)
        {
            hasThrown = true;
        }

        TEST_ASSERT_TRUE(hasThrown);
    }
}
