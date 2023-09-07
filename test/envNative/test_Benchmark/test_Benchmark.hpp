// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>
#include <future>
#include <chrono>

#include <Contract.h>
#include <Benchmark.h>
#include <RingBuffer.h>
#include <ConcurrentRingBuffer.h>

namespace test::envNative::test_Benchmark
{
    void example_function(int x) 
    {
        int sum = 0;
        for (int i = 0; i < x; ++i)
        {
            sum += i;
        }
    }

    void CountingAndAddingTo1000Benchmark() 
    {
        int x = 1'000;
        
        int sum = 0;
        for (int i = 0; i < x; ++i)
        {
            sum += i;
        }
    }

    void DoSomeBenchmarking()
    {
        // auto result = Benchmark::Invoke<1'000'000>(example_function, 10'000);
        auto result = Benchmark::Invoke<1'000'000>(CountingAndAddingTo1000Benchmark);

        // Benchmark::Show(NAMEOF(example_function), result);
        Benchmark::Show(NAMEOF(CountingAndAddingTo1000Benchmark), result);
    }
    
    void TestingSucceeds()
    {
        auto actual = 42;

        auto sut(actual);

        auto result = sut;

        TEST_ASSERT_EQUAL(actual, result);
    }

    void Enqueing1000AndDequeingRingBufferBenchmark()
    {
        using namespace Collections;

        constexpr size_t size = 1'000;
        RingBuffer<int, size> sut;

        for(size_t c = 0; c < size; ++c)
        {
            auto result = sut.Enqueue(c);
        }

        volatile int result;

        while (!sut.IsEmpty())
        {
            auto item = sut.Dequeue();
            if(item) result = *item;
        }
    }

    void Enqueing1000AndDequeingConcurrentRingBufferBenchmark()
    {
        using namespace Collections;

        constexpr size_t size = 1'000;
        ConcurrentRingBuffer<int, size> sut;

        for(size_t c = 0; c < size; ++c)
        {
            auto result = sut.Enqueue(c);
        }

        volatile int result;

        while (!sut.IsEmpty())
        {
            auto item = sut.Dequeue();
            if(item) result = *item;
        }
    }

    void TestConcurrentThreadsSucceeds()
    {
        using namespace std::literals::chrono_literals;
        using namespace Collections;

        constexpr size_t size = 64; 
        ConcurrentRingBuffer<int, size> buffer;
        const size_t itemCount = 1'000;

        size_t itemsEnqueued;
        std::vector<int> dequeuedItems;

        std::thread DoEnqueue([&buffer, &itemsEnqueued, itemCount]
        {
            size_t count = itemCount;
            for(size_t c = 0; c < count; ++c)
            {
                if(buffer.Enqueue(c)) itemsEnqueued++;
            }
        });

        std::thread DoDequeue([&buffer, &dequeuedItems]
        {
            for(;;)
            {
                auto result = buffer.Dequeue();

                if(!result.has_value()) return;

                dequeuedItems.emplace_back(*result);
            }
        });

        DoEnqueue.join();
        DoDequeue.join();
    }
}
