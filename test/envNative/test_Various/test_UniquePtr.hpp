// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <memory>
#include <vector>
#include <cstdint>
#include <stdio.h>
#include <iostream>
#include <algorithm>

#include <Contract.h>

namespace test::envNative::test_Various
{
    class Widget
    {
        private:
            std::unique_ptr<std::vector<uint8_t>> ptr;
            std::vector<uint8_t> v;

        public:
            explicit Widget(std::unique_ptr<std::vector<uint8_t>> data) noexcept
                : ptr(std::move(data))
            {
                // N/A
            }

            explicit Widget(std::vector<uint8_t> data) noexcept
                : v(std::move(data))
            {
                // N/A
            }

            void ShowPtr()
            {
                for(auto u : *ptr)
                {
                    printf("0X%0.2X '%c' (%dd)\n", u, u, u);
                }
            }

            void ShowVec()
            {
                for(auto u : v)
                {
                    printf("0X%0.2X '%c' (%dd)\n", u, u, u);
                }
            }
    };

    void InstantiatingCtorWithUniquePtrSucceeds()
    {
        std::vector<uint8_t> v = { 'A', 'B', 'C', 'D' };

        auto ptr = std::make_unique<std::vector<uint8_t>>(v);

        TEST_ASSERT_EQUAL(v[0], (*ptr)[0]);
        (*ptr)[0] = 'N';
        TEST_ASSERT_NOT_EQUAL(v[0], (*ptr)[0]);

        TEST_ASSERT_NOT_NULL(ptr);
        Widget wPtr(std::move(ptr));
        TEST_ASSERT_NULL(ptr);
        wPtr.ShowPtr();

        TEST_ASSERT_TRUE(0 != v.capacity());
        Widget wVec(std::move(v));
        TEST_ASSERT_TRUE(0 == v.capacity());
        wVec.ShowVec();
    }

    void OnUartReceived()
    {
        // Fixed stack based buffer.
        uint8_t data[512];
        constexpr size_t size = sizeof(data) / sizeof(data[0]);

        int length = 0;

        // Some basic check that we can read the whole buffer.
        // ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t*) &length));
        Contract::Expects([length] { return size >= length; });

        // length = uart_read_bytes(uart_num, data, length, 100);

        // Now that we received that data, we create a vector from it.
        std::vector<uint8_t> bytes(data, data + size);

        // Now bytes holds a copy of 'data'. 
        // To illustrate we change the srd and compare with data from vector.
        TEST_ASSERT_EQUAL(bytes.data()[0], data[0]);
        data[0]++;
        TEST_ASSERT_NOT_EQUAL(bytes.data()[0], data[0]);
    }
}
