/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <algorithm>
#include <cstring>

#include <Contract.h>

#include "Raw.h"

namespace Byd
{
    size_t Byd::tagBytes::CopyTo(void * destination, size_t size, bool initialise)
    {
        constexpr size_t Length = 8;
        
        Contract::Expects([destination] { return nullptr != destination; });
        Contract::Expects([size] { return 0 < size; });

        size_t result = std::min(Length, size);
        
        memcpy(destination, &(this->E0), result);

        if(!initialise) return result;
        if(result >= size) return result;
/*

Case 1: same size
01234567
size:   8
________
length: 8
abcdefgh
min:    8
ret:    8 (no init)

Case 2: destination smaller
012345
size:   6
________
length: 8
abcdefgh
min:    6
ret:    6 (no init)

Case 3: destination larger
0123456789
size:   10
__________
length: 8
abcdefgh
min:    8
ret:    8 (init)

*/
        auto ptr = static_cast<std::byte*>(destination);

        for(auto i = result; i != size; ++i)
        {
            ptr[i] = std::byte(0);
        }

        return result;
    }
}
