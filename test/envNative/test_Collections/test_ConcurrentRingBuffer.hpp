/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <future>
#include <chrono>

#include <unistd.h>

#include <ConcurrentRingBuffer.h>

namespace test::envNative::test_Collections
{
    using namespace std::literals::chrono_literals;

    using namespace Collections;

    void EnqueingItemsToConcurrentRingBufferSucceeds()
    {
        constexpr size_t size = 12;
        ConcurrentRingBuffer<int, size> sut;

        for(size_t c = 0; c < size; ++c)
        {
            auto result = sut.Enqueue(c);

            TEST_ASSERT_TRUE(result);
        }
    }

    void DequeingItemsFromConcurrentRingBufferSucceeds()
    {
        constexpr size_t size = 12;
        ConcurrentRingBuffer<int, size> sut;

        for(size_t c = 0; c < size; ++c)
        {
            auto result = sut.Enqueue(c);

            TEST_ASSERT_TRUE(result);
        }

        for(size_t c = 0; c < size; ++c)
        {
            auto result = sut.Dequeue();

            TEST_ASSERT_TRUE(result.has_value());
            TEST_ASSERT_EQUAL(c, *result);
        }
    }

    void TestConcurrentThreadsSucceeds()
    {
        constexpr size_t size = 64; 
        ConcurrentRingBuffer<int, size> buffer;
        const size_t itemCount = 1000;

        size_t itemsEnqueued;
        std::thread DoEnqueue([&buffer, &itemsEnqueued, &itemCount]
        {
            size_t count = itemCount;
            for(size_t c = 0; c < count; ++c)
            {
                buffer.Enqueue(c);
            }

            itemsEnqueued = count;
        });

        std::this_thread::sleep_for(10ms);

        std::vector<int> dequeuedItems;
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

        TEST_ASSERT_EQUAL(itemCount, itemsEnqueued);
        TEST_ASSERT_LESS_THAN(itemCount, dequeuedItems.size());
        TEST_ASSERT_GREATER_OR_EQUAL(size, dequeuedItems.size());
    }
}
