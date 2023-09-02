/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "Frame.h"

#include "ValidationResult.h"

#ifdef __cpp_lib_expected
    #include <expected>
#else
    #include "Expected.h"
#endif

namespace JkBms
{
    using std::unique_ptr;
    using std::vector;
    using Expected::expected;

    /// @brief Represents the JK-BMS RS485 protocol and its frame.
    class Rs485
    {
        private:
            /// @brief Pointer to the data that make up the JK-BMS RS485 frame.
            const unique_ptr<vector<uint8_t>> ptr;

            /// @brief Representation of a JK-BMS RS485 frame.
            expected<Frame, ValidationResult> frame;

            /// @brief Parses the specified contents of a frame and updates the pointers in frame.
            /// Note: If parsing is not successful, then error will be set to a ValidationResult.
            /// @return Return ValidationResult::Success, if the contents of frame is valid.
            void ParseData() noexcept;

        public:
            Rs485() = delete;
        
            /// @brief .ctor that accepts a vector of uint8_t. Data in vector 
            /// data is moved from and vector is no longer valid when the .ctor returns. 
            Rs485(vector<uint8_t>& data);

            /// @brief .ctor that accepts a unique pointer to a vector of uint8_t.
            /// Ownership of pointer data is transferred to Rs485.
            Rs485(unique_ptr<vector<uint8_t>> data);

            /// @brief Returns elements from the underlying data.
            uint8_t operator[] (size_t index);

            /// @brief Returns the length of the data.
            size_t Length() const { return ptr->size(); }

            /// @brief Returns the data as a vector of bytes.
            const vector<uint8_t>& Data() const { return *ptr; }

            /// @brief Returns the parsed frame.
            const expected<Frame, ValidationResult>& Frame() const { return frame; }

            /// @brief Determines wether the frame is valid.
            /// @return True, if the frame is valid; false, otherwise.
            bool IsValid() const noexcept { return frame.has_value(); }

            /// @brief Returns the result of the last frame validation.
            /// @return Return ValidationResult::Success, if the contents of frame is valid.
            ValidationResult GetValidationResult() const noexcept { return IsValid() ? ValidationResult::Success : frame.error(); }
    };
}
