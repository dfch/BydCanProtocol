/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <stdexcept>

#include <unity.h>

#include <Contract.h>

#include <Retry.h>

namespace test::envNative::test_Threading
{
    using namespace Threading;

    void RetrySucceeds()
    {
        int arbitraryDefaultResult = 42;
        auto const expected = 3;
        auto counter = 0;

        RetryStrategyFixed strategy;
        auto result = Retry<int>::Invoke([&counter, expected]() mutable -> int
        {
            printf("%s: Counter: %d\n", NAMEOF(Retry), counter);
            counter++;
            
            if(expected > counter)
            {
                throw std::runtime_error("Exception thrown on purpose to simulate a failure.");
            }

            return counter;
        }, strategy, [arbitraryDefaultResult] { return arbitraryDefaultResult; });

        TEST_ASSERT_EQUAL(expected, counter);
    }

    void InvokingRetryWithDefaultResultSucceeds()
    {
        int arbitraryDefaultResult = 42;
        auto const expected = 3;
        auto counter = 0;

        RetryStrategyFixed strategy;
        strategy.WaitTimeMaxMilliseconds = 100;

        auto result = Retry<int>::Invoke([&counter, expected]() mutable -> int
        {
            throw std::runtime_error("Exception thrown on purpose to simulate a failure.");
        }, strategy, [arbitraryDefaultResult] { return arbitraryDefaultResult; });

        TEST_ASSERT_EQUAL(arbitraryDefaultResult, result);
    }
}
