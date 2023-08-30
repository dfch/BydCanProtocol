/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>
#include <vector>
#include <cstdint>

#include <cstring>

namespace test::envNative::test_Various
{
    void TestVector()
    {
        std::vector<std::uint8_t> data { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };
        
        uint32_t dest;

        size_t position = 0;

        std::memcpy(&dest, data.data() +position, sizeof(dest));
        printf("%d: 0x%08X\n", position, dest);
        position++;

        std::memcpy(&dest, data.data() +position, sizeof(dest));
        printf("%d: 0x%08X\n", position, dest);
        position++;

        std::memcpy(&dest, data.data() +position, sizeof(dest));
        printf("%d: 0x%08X\n", position, dest);
        position++;

        std::memcpy(&dest, data.data() +position, sizeof(dest));
        printf("%d: 0x%08X\n", position, dest);

        position = 0;
    }
}
