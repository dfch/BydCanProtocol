// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <unity.h>

#include "test_Benchmark.hpp"

extern "C"
{
    // Run tests for this folder by running this command:
    // [path-to-platformio]platformio.exe test --environment [your-env] --verbose --filter */test_Template
    namespace test::envNative::test_Benchmark
    {
        using namespace Benchmark;
        
        int runUnityTests()
        {
            UNITY_BEGIN();

            RUN_BENCHMARK(CountingAndAddingTo1000Benchmark);
            RUN_BENCHMARK(Enqueing1000AndDequeingRingBufferBenchmark);
            RUN_BENCHMARK(Enqueing1000AndDequeingConcurrentRingBufferBenchmark);
            RUN_BENCHMARK(TestConcurrentThreadsSucceeds);

            return UNITY_END();
        }

        void setUp(void)
        {
            // N/A
        }

        void tearDown(void)
        {
            // N/A
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
