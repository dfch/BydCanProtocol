/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#include "Thread.h"

namespace Threading
{
    void Thread::Sleep(uint32_t waitTimeMilliseconds)
    {
        vTaskDelay(waitTimeMilliseconds / portTICK_PERIOD_MS);
    }

    void Thread::Start(TaskFunction_t func, const char* name, void* pvParameters)
    {
        TaskHandle_t handle = NULL;

        xTaskCreate(func, name, stackSizeInWordsDefault, pvParameters, priorityDefault, &handle);
    }
}

#endif
