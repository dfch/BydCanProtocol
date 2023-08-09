/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#pragma once

#include <cstdint>
#include <cstddef>

#include "../Constants.h"

namespace Byd
{
    /// @brief Represents the raw data of a message in bytes.
    typedef struct tagBytes
    {
        std::byte E0;
        std::byte E1;
        std::byte E2;
        std::byte E3;
        std::byte E4;
        std::byte E5;
        std::byte E6;
        std::byte E7;

        /// @brief Copies the contents of Bytes to destination. The number of bytes copied is the lesser of size and the size of Bytes.
        /// @param destination A pointer to a location that must hold at maximum the size of Bytes.
        /// @param size The number of bytes to be copied. If the size of Bytes is smaller than size, then only the size of Bytes is copied.
        /// @param initialise True, if the destination buffer will be initialised with 0. False, otherweise. Default: False.
        /// @return The number of bytes copied from Bytes.
        size_t CopyTo(void * destination, size_t size, bool initialise = false);
    } Bytes;

    /// @brief Represents the raw data of a message in uint8_t.
    typedef struct tagUint8s
    {
        uint8_t E0;
        uint8_t E1;
        uint8_t E2;
        uint8_t E3;
        uint8_t E4;
        uint8_t E5;
        uint8_t E6;
        uint8_t E7;
    } Uint8s;

    /// @brief Represents the raw data of a message in int8_t.
    typedef struct tagInt8s
    {
        int8_t E0;
        int8_t E1;
        int8_t E2;
        int8_t E3;
        int8_t E4;
        int8_t E5;
        int8_t E6;
        int8_t E7;
    } Int8s;

    /// @brief Represents the raw data of a message in uint16_t.
    typedef struct tagUint16s
    {
        uint16_t E0;
        uint16_t E1;
        uint16_t E2;
        uint16_t E3;
    } Uint16s;

    /// @brief Represents the raw data of a message in int16_t.
    typedef struct tagInt16s
    {
        int16_t E0;
        int16_t E1;
        int16_t E2;
        int16_t E3;
    } Int16s;

    /// @brief Represents the raw data of a message in uint32_t.
    typedef struct tagUint32s
    {
        uint32_t E0;
        uint32_t E1;
    } Uint32s;


    typedef struct tagInt32s
    {
        int32_t E0;
        int32_t E1;
    } Int32s;

    /// @brief Represents the raw data of a message in different types.
    typedef union tagRaw
    {
        Byd::Bytes Bytes;
        Byd::Uint8s Uint8s;
        Byd::Int8s Int8s;
        Byd::Uint16s Uint16s;
        Byd::Int16s Int16s;
        Byd::Uint32s Uint32s;
        Byd::Int32s Int32s;
        char CharArray[DataLength];
        std::byte ByteArray[DataLength];
    } Raw;
}
