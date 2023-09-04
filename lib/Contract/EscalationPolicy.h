// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

namespace Contract
{
    /// @brief Defines policies to follow on assertion failures.
    enum class EscalationPolicy
    {
        Ignore, // Ignores an assertion failure.
        Log, // Logs an assertion failure.
        Throw, // Throws an exception on an assertion failure. catch() possible.
        Abort, // Aborts the program on an assertion failure. No catch() possible.
    };
}
