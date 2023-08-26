/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include "Rs485.h"

#include <cstddef>

#include <Contract.h>

using JkBms::Rs485;

namespace JkBms
{
    // Rs485::Rs485(std::vector<std::byte> data)
    // {
    //     this->data = data;
    // }

    Rs485::Rs485(std::vector<std::byte> &data)
    {
        this->data = data;
    }

    Rs485::Rs485(std::byte *data, size_t length)
    {
        Contract::Requires([data] { return nullptr != data; });

        this->data = std::vector<std::byte>(data, data + length);
    }

    std::byte Rs485::operator[] (std::size_t index)
    {
        Contract::Requires([this, index] { return index < this->data.size(); }, Contract::ErrorCode::OutOfRange);

        auto result = this->data[index];

        return result;
    }
}
