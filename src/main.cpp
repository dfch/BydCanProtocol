/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <Program.h>

extern "C"
{
    /// @brief Entry point of the espidf framework.
    void app_main()
    {
        #if defined(ESP_PLATFORM)

            Program::Program::Factory::Create()->Invoke();

        #endif
    }

    /// @brief C/C++ entry point of the application.
    int main()
    {
        app_main();

        return 0;
    }
}
