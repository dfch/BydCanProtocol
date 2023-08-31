/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <vector>
#include <cstdint>
#include <memory>
#include <type_traits>

#include "Frame.h"

#include "ValidationResult.h"

namespace JkBms
{
    using std::unique_ptr;
    using std::vector;

    /// @brief Represents the JK-BMS RS485 protocol.
    class Rs485
    {
        private:
            ValidationResult validationResult;

            /// @brief Pointer to the data that make up the JK-BMS RS485 frame.
            const unique_ptr<vector<uint8_t>> ptr;

            /// @brief Representation of a JK-BMS RS485 frame.
            Frame frame;

        public:
            Rs485() = delete;
        
            /// @brief .ctor that accepts a vector of uint8_t.
            Rs485(vector<uint8_t>& data);

            /// @brief .ctor that accepts a unique pointer to a vector of uint8_t.
            Rs485(unique_ptr<vector<uint8_t>> data);

            /// @brief Returns elements from the underlying data.
            uint8_t operator[] (size_t index);

            /// @brief Returns the length of the data.
            size_t Length() const { return ptr.get()->size(); }

            /// @brief Returns the data as a vector of bytes.
            const vector<uint8_t>& Data() const { return *ptr; }

            /// @brief Returns the parsed frame.
            const Frame& Frame() const { return frame; }

            /// @brief Determines wether the frame is valid.
            /// @return True, if the frame is valid; false, otherwise.
            bool IsValid() const noexcept { return ValidationResult::Success == validationResult; }

            /// @brief Returns the result of the last frame validation.
            /// @return Return ValidationResult::Success, if the contents of frame is valid.
            ValidationResult GetValidationResult() const noexcept { return validationResult; }

            /// @brief Validates the specified contents of a frame.
            /// @return Return ValidationResult::Success, if the contents of frame is valid.
            ValidationResult Validate() noexcept;
    };
}
