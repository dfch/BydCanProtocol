/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>
#include <unistd.h>
#include <pthread.h>

namespace Threading
{
    /// @brief Represents a threading class with convenience functions.
    class Thread
    {
        private:
            /// @brief Represents the default stack size in words.
            static constexpr uint32_t stackSizeInBytesDefault = 4096;

            /// @brief Represents the default thread priority.
            static const int priorityDefault = 5;

            /// @brief Default .ctor. Not supported.
            Thread() = delete;

        public:
            /// @brief Suspends the current thread for the specified amount of time.
            /// @param waitTimeMilliseconds The amount of time to suspend the current thread.
            static void Sleep(uint32_t waitTimeMilliseconds);

            /// @brief Creates a new task.
            /// @param taskFunction The task function.
            /// @param arg The parameters to pass to the task.
            static void Start(void *(*taskFunction)(void *arg), void *arg);

            /// @brief Creates a new task.
            /// @param taskFunction The task function.
            /// @param arg The parameters to pass to the task.
            /// @param stackSize The size of the stack in bytes.
            static void Start(void *(*taskFunction)(void *arg), void *arg, int32_t stackSize);

    };
}
