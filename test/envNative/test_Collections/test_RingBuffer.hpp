/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include <RingBuffer.h>

namespace test::envNative::test_Collections
{
    using namespace Collections;

    void EnqueingItemsToRingBufferSucceeds()
    {
        constexpr size_t size = 12;
        RingBuffer<int, size> sut;

        for(size_t c = 0; c < size; ++c)
        {
            auto result = sut.Enqueue(c);

            TEST_ASSERT_TRUE(result);
        }
    }

    void DequeingItemsFromRingBufferSucceeds()
    {
        constexpr size_t size = 12;
        RingBuffer<int, size> sut;

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

    void EnqueingMoreItemsThanSizeToRingBufferSucceeds()
    {
        constexpr size_t size = 12;
        RingBuffer<int, size> sut;

        for(size_t c = 0; c < size; ++c)
        {
            auto result = sut.Enqueue(c);

            TEST_ASSERT_TRUE(result);
        }

        for(size_t c = 0; c < 2* size; ++c)
        {
            auto result = sut.Enqueue(c);

            TEST_ASSERT_FALSE(result);
        }
    }

    void EnqueingMoreItemsThanSizeToRingBufferMovesDequeueIndexSucceeds()
    {
        constexpr size_t size = 12;
        RingBuffer<int, size> sut;

        for(size_t c = 0; c < size; ++c)
        {
            auto result = sut.Enqueue(c);

            TEST_ASSERT_TRUE(result);
        }
        
        // Add a 13th element to the queue.
        auto c = size + 1;
        sut.Enqueue(c);

        // Now the 0th element is overwritten and receive the 1st element.
        auto result = sut.Dequeue();
        TEST_ASSERT_TRUE(result.has_value());
        TEST_ASSERT_EQUAL(1, *result);
    }

    void DequeingFromEmptyRingBufferReturnsEmptyElement()
    {
        constexpr size_t size = 12;
        RingBuffer<int, size> sut;

        auto result = sut.Dequeue();
        TEST_ASSERT_FALSE(result.has_value());
    }

    void EmptyingRingBufferSucceeds()
    {
        constexpr size_t size = 12;
        RingBuffer<int, size> sut;

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

        auto result = sut.Dequeue();
        TEST_ASSERT_FALSE(result.has_value());
    }
}
