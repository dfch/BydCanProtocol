/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <vector>
#include <cstdint>
#include <cstddef>
#include <memory>

#include "Frame.h"

#include "ValidationResult.h"

namespace JkBms
{
    /// @brief Represents the JK-BMS RS485 protocol.
    class Rs485
    {
        private:
            /// @brief The data that make up the JK-BMS RS485 message.
            std::vector<uint8_t> data;

            Frame frame;

        public:
            /// @brief Default .ctor.
            Rs485() = delete;
        
            /// @brief .ctor that accepts a reference to a vector of uint8_t.
            Rs485(std::vector<uint8_t>& data);

            /// @brief .ctor that accepts a raw uint8_t array.
            Rs485(uint8_t* data, size_t length);

            /// @brief Overloads the [] operator to access the data.
            uint8_t operator[] (size_t index);

            /// @brief Gets the length of the data.
            size_t Length() const { return this->data.size(); }

            /// @brief Gets the data as a vector of bytes.
            const std::vector<uint8_t>& GetData() const { return this->data; }

            /// @brief Determines whether the specified contents of a Frame is valid or not.
            /// @return Return true, if the contents of Frame is valid; false, otherwise.
            ValidationResult IsValid() const noexcept;
    };
}
