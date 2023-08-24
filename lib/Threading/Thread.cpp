/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <ctime>
#include <unistd.h>
#include <pthread.h>

#include "Thread.h"
#include <Contract.h>
    
namespace Threading
{
    void Thread::Sleep(uint32_t waitTimeMilliseconds)
    {
        usleep(waitTimeMilliseconds * 1000);
    }

    void Thread::Start(void *(*start_routine)(void *arg), void *arg)
    {
        Start(start_routine, arg, stackSizeInBytesDefault);
    }

    void Thread::Start(void *(*start_routine)(void *arg), void *arg, int32_t stackSize)
    {
        pthread_t threadId;
        pthread_attr_t attributes;
        pthread_attr_init(&attributes);
        // For whatever reason on env:native with at least MSYS2 G++ running on Windows
        // `stacksize` and `detachstate` are not defined.
        #if defined(ESP_PLATFORM)
        attributes.stacksize = stackSize;
        attributes.detachstate = PTHREAD_CREATE_DETACHED;
        #endif

        auto result = pthread_create(&threadId, &attributes, start_routine, arg);
        Contract::Requires([result] { return 0 == result; }, NAMEOF(result));
    }
}
