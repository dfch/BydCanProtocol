// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include <memory>
#include <vector>

namespace test::envNative::test_Various
{
    class Thing
    {
        private:

        Thing() noexcept
        {
            // Do something.
        }

        Thing(int flag) noexcept
        {
            // Do something.
        }

        friend std::unique_ptr<Thing> std::make_unique<Thing>();
        // friend std::unique_ptr<Thing> std::make_unique<Thing>(int);
        // friend template< class Thing, class... Args >
        //     std::unique_ptr<Thing> std::make_unique( Args&&... args );
        
        public:

        int ReturnsTrue()
        {
            return true;
        }

        class Factory
        {
            public:

            static std::unique_ptr<Thing> Create()
            {
                std::unique_ptr<Thing> result = std::make_unique<Thing>();

                return result;
            }
        };
    };
    
    void MakeUniqueAccessingPrivateCtorSucceeds()
    {
        auto sut = Thing::Factory::Create();

        auto result = sut->ReturnsTrue();

        TEST_ASSERT_TRUE(result);
    }
}