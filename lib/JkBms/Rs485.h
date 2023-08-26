/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>

namespace JkBms
{
    /// @brief Represents the JK-BMS RS485 protocol.
    class Rs485
    {
        private:
            /// @brief The data that make up the JK-BMS RS485 message.
            std::vector<std::byte> data;


        public:
            /// @brief Default .ctor.
            Rs485() = delete;
        
            // /// @brief .ctor that accepts a vector of bytes.
            // Rs485(std::vector<std::byte> data);

            /// @brief .ctor that accepts a reference to a vector of bytes.
            Rs485(std::vector<std::byte>& data);

            /// @brief .ctor that accepts a vector of uint8_t.
            Rs485(std::vector<uint8_t> data);

            /// @brief .ctor that accepts a reference to a vector of uint8_t.
            Rs485(std::vector<uint8_t>& data);

            /// @brief .ctor that accepts a raw byte array.
            Rs485(std::byte* data, size_t length);

            /// @brief .ctor that accepts a raw uint8_t array.
            Rs485(uint8_t* data, size_t length);

            /// @brief Overloads the [] operator to access the data.
            std::byte operator[] (std::size_t index);

            /// @brief Gets the length of the data.
            size_t Length() const { return this->data.size(); }

            /// @brief Gets the data as a vector of bytes.
            const std::vector<std::byte>& GetData() const { return this->data; }

    };
}
