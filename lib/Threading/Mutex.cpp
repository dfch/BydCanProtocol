/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#if defined(ESP_PLATFORM)

#include <esp_timer.h>

#include "Mutex.h"

#include <Contract.h>

namespace Threading
{
    Mutex::Mutex()
    {
        auto result = pthread_mutex_init(&mutex, NULL);
        Contract::Expects([result] { return 0 == result; }, "Mutex could not be created.");
    }

    Mutex::~Mutex()
    {
        if(nullptr == &mutex) return;
        
        pthread_mutex_destroy(&mutex);
    }

    Mutex::Mutex(Mutex&& other) noexcept
    {
        Contract::Expects([&other] { return nullptr != &other.mutex; }, "Mutex is not initialized.");

        mutex = other.mutex;
        other.mutex = (pthread_mutex_t) nullptr;
    }

    bool Mutex::Wait()
    {
        return Wait(Timeout::Infinite);
    }

    bool Mutex::Wait(int32_t timeout)
    {
        if (Timeout::Infinite == timeout)
        {
            auto result = pthread_mutex_lock(&mutex);
            Contract::Expects([result] { return 0 == result; }, "Mutex could not be locked.");

            return true;
        }

        // Simple spin "lock".
        auto now = esp_timer_get_time();
        do
        {
            auto result = pthread_mutex_trylock(&mutex);
            if (0 == result) return true;
            
        } while (esp_timer_get_time() - now < timeout);
        
        return false;
    }

    bool Threading::Mutex::Release()
    {
        auto result = pthread_mutex_unlock(&mutex);

        return 0 == result;
    }

    bool Mutex::Signal()
    {
        return Signal(Timeout::Infinite);
    }

    bool Mutex::Signal(int32_t timeout)
    {
        return WaitAndRelease([] {}, timeout);
    }

    bool Threading::Mutex::WaitAndRelease(std::function<void()> func)
    {
        return WaitAndRelease(func, Timeout::Infinite);
    }

    bool Threading::Mutex::WaitAndRelease(std::function<void()> func, int32_t timeout)
    {
        auto isLocked = false;
        auto isCompleted = false;

        try
        {
            auto result = Wait(timeout);
            if(!result) return false;

            isLocked = true;

            func();
            isCompleted = true;
        }
        catch(const std::exception& e)
        {
            if(!isLocked) throw e;

            Release();
            isLocked = false;
        }

        if(isLocked) Release();

        return isCompleted;
    }
}

#endif
