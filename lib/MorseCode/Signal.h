/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

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
