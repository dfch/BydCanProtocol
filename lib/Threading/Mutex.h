/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#pragma once

#include <cstdint>
#include <functional>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <pthread.h>

namespace Threading
{
    // @brief Contains constants that specify infinite time-out intervals. 
    class Timeout
    {
        public:
            // @brief Represents an infinite waiting period, or infinite time-out.
            static constexpr int32_t Infinite = -1;
    };

    // Create a mutex class similar to .NET that uses the EspressIDF framework.
    // Also show required include files.
    // Generate move constructor and move assignment operator.

    class Mutex
    {
        private:
            // @brief The mutex.
            pthread_mutex_t mutex;
            
        public:
            // @brief Default .ctor.
            Mutex();

            // @brief Destructor.
            ~Mutex();

            // @brief Move constructor.
            // @param other The other instance.
            // @return The current instance.
            Mutex(Mutex&& other) noexcept;

            // @brief Move assignment operator. Not supported.
            // @param other The other instance.
            // @return The current instance.
            Mutex& operator=(Mutex&& other) = delete;

            // @brief Copy constructor. Not supported.
            // @return The current instance.
            Mutex(const Mutex&) = delete;

            // @brief Copy assignment operator. Not supported.
            // @return The current instance.
            Mutex& operator=(const Mutex&) = delete;

            // @brief Blocks the current thread until the current Mutex receives a signal.
            // @return True if the current instance receives a signal. If the current instance is never signaled, Wait never returns.
            bool Wait();

            // @brief Blocks the current thread until the current Mutex receives a signal.
            // @param timeout The number of milliseconds to wait, or Timeout::Infinite (-1) to wait indefinitely.
            bool Wait(int32_t timeout);

            // @brief Releases the lock on the mutex.
            // @return True if the current instance is released; otherwise, false.
            bool Release();

            // @brief Signals and releases a Mutex.
            // @return True if the current instance is signaled; otherwise, false. If the current instance is never signaled, Wait never returns.
            bool Signal();

            // @brief Signals and releases a Mutex.
            // @param timeout The number of milliseconds to wait, or Timeout::Infinite (-1) to wait indefinitely.
            // @return True if the current instance is signaled; otherwise, false. If the current instance is never signaled, Wait never returns.
            bool Signal(int32_t timeout);

            // @brief Blocks the current thread until the current Mutex receives a signal and then executes the given function.
            // @param func The function to execute.
            // @return True if the current instance receives a signal and the function is executed; otherwise, false.
            bool WaitAndRelease(std::function<void()> func);

            // @brief Blocks the current thread until the current Mutex receives a signal and then executes the given function.
            // @param func The function to execute.
            // @param timeout The number of milliseconds to wait, or Timeout::Infinite (-1) to wait indefinitely.
            // @return True if the current instance receives a signal and the function is executed; otherwise, false.
            bool WaitAndRelease(std::function<void()> func, int32_t timeout);
    };
}

#endif
