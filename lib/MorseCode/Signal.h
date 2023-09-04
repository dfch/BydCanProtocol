// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#pragma once

namespace MorseCode
{
    /// @brief Represents a signal.
    typedef enum signal
    {
        Dit, // A short signal.
        Dah, // A long signal.
        Char, // A character spacing.
        Word, // A word spacing.
    } Signal;
}
