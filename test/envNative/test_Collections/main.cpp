/**
* Copyright (c) Ronald Rink
* See LICENSE file in the project root for full license information.
*/

#include <unity.h>

#include "test_RingBuffer.hpp"
#include "test_ConcurrentRingBuffer.hpp"

extern "C"
{
    namespace test::envNative::test_Collections
    {
        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
        }

        int runUnityTests(void)
        {
            UNITY_BEGIN();

            // #include "test_RingBuffer.hpp"
            RUN_TEST(EnqueingItemsToRingBufferSucceeds);
            RUN_TEST(DequeingItemsFromRingBufferSucceeds);
            RUN_TEST(EnqueingMoreItemsThanSizeToRingBufferSucceeds);
            RUN_TEST(EnqueingMoreItemsThanSizeToRingBufferMovesDequeueIndexSucceeds);
            RUN_TEST(DequeingFromEmptyRingBufferReturnsEmptyElement);
            RUN_TEST(EmptyingRingBufferSucceeds);

            // #include "test_ConcurrentRingBuffer.hpp"
            RUN_TEST(EnqueingItemsToConcurrentRingBufferSucceeds);
            RUN_TEST(DequeingItemsFromConcurrentRingBufferSucceeds);
            RUN_TEST(TestConcurrentThreadsSucceeds);

            return UNITY_END();
        }

        void app_main() 
        {
            runUnityTests();
        }

        int main(int argc, char **argv)
        {
            return runUnityTests();
        }
    }
}
