// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <vector>
#include <mutex>
#include <optional>

namespace Collections
{
    /// @brief Base class for ring buffer.
    /// @tparam T Type of items the ring buffer stores.
    /// @tparam TSize The number of elements the ring buffer can store.
    template<typename T, size_t TSize>
    class RingBufferBase
    {
        protected:
            const size_t Empty = 0;
            const size_t Increment = 1;

            int Counter;
            
            size_t DequeueIndex;
            size_t EnqueueIndex;

            std::vector<T> Data;

        public:
            /// @brief Constructor that initialises the ring buffer.
            explicit RingBufferBase()
                : Data(TSize), Counter(Empty), DequeueIndex(Empty), EnqueueIndex(Empty) { }

            RingBufferBase(const RingBufferBase& other) = delete;
            RingBufferBase& operator=(const RingBufferBase& other) = delete;
            RingBufferBase(RingBufferBase&& other) = delete;
            RingBufferBase& operator=(RingBufferBase&& other) = delete;

            /// @brief Enqueues an item into the ring buffer.
            /// @param item The item of type T to enqueue.
            /// @return Returns true, if the item could be enqueued without overwriting the buffer; false, otherwise.
            virtual bool Enqueue(T value) = 0;

            /// @brief Dequeues an item from the ring buffer.
            /// @return Returns an item of type T; or NULL, if queue is empty.
            virtual std::optional<T> Dequeue() = 0;

            /// @brief Determines whether the ring buffer is empty or not.
            /// @return True, if empty; false, otherwise.
            bool IsEmpty()
            {
                return Empty == Counter;
            }

            /// @brief Returns the number of items in the ring buffer.  
            /// @return The number of items in the ring buffer.
            size_t Size()
            {
                return Counter;
            }
    };
}
