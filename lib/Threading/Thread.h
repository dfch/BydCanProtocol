/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#pragma once

#include <cstdint>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace Threading
{
    /// @brief Represents a threading class with convenience functions.
    class Thread
    {
        private:
            /// @brief Represents the default stack size in words.
            static const uint32_t stackSizeInWordsDefault = 2048;

            /// @brief Represents the default thread priority.
            static const int priorityDefault = 5;

            /// @brief Default .ctor. Not supported.
            Thread() = delete;

        public:
            /// @brief Suspends the current thread for the specified amount of time.
            /// @param waitTimeMilliseconds The amount of time to suspend the current thread.
            static void Sleep(uint32_t waitTimeMilliseconds);

            /// @brief Creates a new task.
            /// @param task The task function.
            /// @param name The name of the task.
            /// @param pvParameters The parameters to pass to the task.
            static void Start(TaskFunction_t task, const char* name, void* pvParameters);
            
    };
}

#endif
