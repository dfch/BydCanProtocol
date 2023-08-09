/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <Contract.h>

using Contract::Requires;
using Contract::ErrorCode;

extern "C"
{
    namespace test::envNative::test_Contract
    {
        class ArbitraryClass
        {
            public:
                bool ThrowsOnTrue(bool flag)
                {
                    Requires([flag] { return !flag; }, ErrorCode::InvalidArgument);

                    return !flag;
                }

                bool ThrowsOnTrueWithDefaultArgument(bool flag)
                {
                    Requires([flag] { return !flag; });

                    return !flag;
                }

        };

        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        void RequiresDoesNotThrow()
        {
            ArbitraryClass sut;

            auto result = sut.ThrowsOnTrue(false);

            TEST_ASSERT_TRUE(result);
        }

        void RequiresDoesThrow()
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

        void RequiresDoesThrowWithDefaultArgument()
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

        int runUnityTests(void)
        {
            UNITY_BEGIN();

            RUN_TEST(RequiresDoesNotThrow);
            RUN_TEST(RequiresDoesThrow);
            RUN_TEST(RequiresDoesThrowWithDefaultArgument);

            return UNITY_END();
        }

        void app_main() 
        {
            runUnityTests();
        }

        int main(int argc, char **argv)
        {
            return runUnityTests();
        }
    }
}
