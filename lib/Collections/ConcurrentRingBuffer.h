// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <optional>
#include <mutex>

#include "RingBufferBase.h"

namespace Collections
{
    /// @brief Implements a thread safe ring buffer.
    /// @tparam T Type of items the ring buffer stores.
    /// @tparam TSize The number of elements the ring buffer can store.
    template<typename T, size_t TSize>
    class ConcurrentRingBuffer : public RingBuffer<T, TSize>
    {
        private:
            std::mutex mutex;

        public:
            /// @brief Enqueues an item into the ring buffer.
            /// @param item The item of type T to enqueue.
            /// @return Returns true, if the item could be enqueued without overwriting the buffer; false, otherwise.
            bool Enqueue(T value) override
            {
                const std::scoped_lock<std::mutex> lock(mutex);

                return RingBuffer<T, TSize>::Enqueue(value);
            }

            /// @brief Dequeues an item from the ring buffer.
            /// @return Returns an item of type T; or NULL, if queue is empty.
            std::optional<T> Dequeue() override
            {
                const std::scoped_lock<std::mutex> lock(mutex);
                
                return RingBuffer<T, TSize>::Dequeue();
            }
    };
}
