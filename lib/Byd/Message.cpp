/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <memory>
#include <cstring>

#include "Message.h"

namespace Byd
{
    Message::Message()
    {
        // N/A
    }

    Byd::Raw Message::SerialiseData()
    {
        auto result = std::visit( [] (auto v) -> Byd::Raw
        {
            auto ptr = (char*)(void*) &v;

            Byd::Raw raw;
            std::memcpy(raw.CharArray, ptr, DataLength);

            return raw;
        }, Data );

        return result;
    }
}
