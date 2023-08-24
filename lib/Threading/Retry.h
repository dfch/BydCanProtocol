/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>
#include <functional>
#include <ctime>
#include <unistd.h>
#include <algorithm>

#include "Thread.h"

namespace Threading
{
    class RetryStrategyBase
    {
        public:
            uint32_t MaxAttempts = UINT32_MAX;
            uint32_t CurrentAttempt = 1;
            uint32_t WaitTimeDefaultMilliseconds = 10;
            uint32_t WaitTimeMaxMilliseconds = 300 * 1000;
            uint32_t WaitTimeIntervalMinMilliseconds = 200;
            uint32_t WaitTimeIntervalMaxMilliseconds = 20 * 1000;
            uint32_t NextAttempt()
            {
                return ++CurrentAttempt;
            }

            virtual uint32_t GetNextWaitTime(uint32_t currentWaitTime) = 0;
    };

    class RetryStrategyFixed : public RetryStrategyBase
    {
        public:
            uint32_t WaitTimeDefaultMilliseconds = 250;

            uint32_t GetNextWaitTime(uint32_t currentWaitTime) override
            {
                return WaitTimeDefaultMilliseconds;
            }
    };

    template<typename TResult>
    class Retry
    {
        public:
            static TResult Invoke(std::function<TResult()> func, RetryStrategyBase& strategy)
            {
                TResult result;
                uint32_t waitTimeMilliseconds = strategy.WaitTimeIntervalMinMilliseconds;
                
                // Temporarily disabled because we do not want to use Thread.h
                // auto start = esp_timer_get_time();
                struct timespec tsStart;
                clock_gettime(CLOCK_REALTIME, &tsStart);

                for(;;)
                {
                    try
                    {
                        return func();
                    }
                    catch (const std::exception& ex)
                    {
                        // Intentinally do nothing. We will retry.
                    }

                    if (strategy.NextAttempt() > strategy.MaxAttempts) break;

                    struct timespec tsNow;
                    clock_gettime(CLOCK_REALTIME, &tsNow);
                    
                    auto diffMilliseconds = (tsNow.tv_sec - tsStart.tv_sec) * 1e3 + 
                        (tsNow.tv_nsec - tsStart.tv_nsec) / 1e6;
                    if(diffMilliseconds >= strategy.WaitTimeMaxMilliseconds) break;

                    auto nextWaitTime = strategy.GetNextWaitTime(waitTimeMilliseconds);
                    waitTimeMilliseconds = std::min(nextWaitTime, strategy.WaitTimeIntervalMaxMilliseconds);
                    // Temporarily disabled because we do not want to use Thread.h
                    // Threading::Thread::Sleep(waitTimeMilliseconds);
                    usleep(waitTimeMilliseconds * 1000);
                }

                return defaultResult;
            }
        private:
            static const TResult defaultResult();
    };
}
