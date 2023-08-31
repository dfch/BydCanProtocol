/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>
#include <optional>

#include "RingBufferBase.h"

namespace Collections
{
    /// @brief Implements a non-thread safe ring buffer.
    /// @tparam T Type of items the ring buffer stores.
    /// @tparam TSize The number of elements the ring buffer can store.
    template<typename T, size_t TSize>
    class RingBuffer : public RingBufferBase<T, TSize>
    {
        using RingBufferBase<T, TSize>::Counter;
        using RingBufferBase<T, TSize>::EnqueueIndex;
        using RingBufferBase<T, TSize>::DequeueIndex;
        using RingBufferBase<T, TSize>::Increment;
        using RingBufferBase<T, TSize>::Data;
        using RingBufferBase<T, TSize>::Empty;

        public:
            /// @brief Enqueues an item into the ring buffer.
            /// @param item The item of type T to enqueue.
            /// @return Returns true, if the item could be enqueued without overwriting the buffer; false, otherwise.
            virtual bool Enqueue(T value) override
            {
                if(TSize == Counter)
                {
                    // Buffer full. Counter does not change.
                    Data[EnqueueIndex] = value;
                    EnqueueIndex = (EnqueueIndex + Increment) % TSize;
                    DequeueIndex = (DequeueIndex + Increment) % TSize;

                    return false;
                }
                
                auto next = (Counter + Increment) % TSize;
                Counter = Empty == next ? TSize : next;
                Data[EnqueueIndex] = value;
                EnqueueIndex = (EnqueueIndex + Increment) % TSize;

                return true;
            }

            /// @brief Dequeues an item from the ring buffer.
            /// @return Returns an item of type T; or NULL, if queue is empty.
            virtual std::optional<T> Dequeue() override
            {
                if(Empty == Counter)
                {
                    // Buffer empty. Counter does not change.

                    return {};
                }

                --Counter;
                T result = Data[DequeueIndex];
                DequeueIndex = (DequeueIndex + Increment) % TSize;

                return result;
            }
    };
}
