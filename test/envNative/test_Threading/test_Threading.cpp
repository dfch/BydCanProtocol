/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <stdexcept>

#include <unity.h>

#include <Retry.h>
#include <Contract.h>

extern "C"
{
    namespace test::envEmbedded::test_Threading
    {
        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        void RetrySucceeds()
        {
            auto const expected = 3;
            auto counter = 0;

            Threading::RetryStrategyFixed strategy;
            auto result = Threading::Retry<int>::Invoke([&counter, expected]() mutable -> int
            {
                printf("%s: Counter: %d\n", NAMEOF(Threading::Retry), counter);
                counter++;
                
                if(expected > counter)
                {
                    throw std::runtime_error("Exception thrown on purpose to simulate a failure.");
                }

                return counter;
            }, strategy);

            TEST_ASSERT_EQUAL(expected, counter);
        }

        int runUnityTests(void)
        {
            UNITY_BEGIN();

            RUN_TEST(RetrySucceeds);

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
