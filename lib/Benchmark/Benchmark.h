// Copyright (c) 2023 Ronald Rink
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
// SPDX-License-Identifier: MIT

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <functional>
#include <numeric>
#include <string>
#include <unity.h>
#include <vector>

namespace Benchmark
{
    using namespace std;
    using namespace std::chrono;

    /// @brief Benchmarks a given function TFunc and returns its average and medium execution time.
    /// @tparam TSize The number of times 
    /// @tparam TFunc The type of the function to benchmark.
    /// @tparam ...TArgs Variadic parameters of the callable.
    /// @param func The function to benchmark.
    /// @param ...args Parameters of the callable.
    /// @return Returns a pair containing the average and medium execution time in nanoseconds.
    template<size_t TSize, typename TFunc, typename... TArgs>
    pair<nanoseconds, nanoseconds> Invoke(TFunc&& func, TArgs&&... args) 
    {
        vector<nanoseconds> durations;

        // First run is not measured.
        func(forward<TArgs>(args)...);

        // Messure execution time.
        for(size_t c = 0; c < TSize; ++c) 
        {
            auto now = high_resolution_clock::now();
            func(forward<TArgs>(args)...);
            auto elapsed = high_resolution_clock::now() - now;

            durations.push_back(duration_cast<nanoseconds>(elapsed));
        }

        // Calculate average.
        auto sum = accumulate(durations.begin(), durations.end(), nanoseconds(0));
        auto average = sum / TSize;

        // Calculate median.
        sort(durations.begin(), durations.end());
        nanoseconds median = 0 == TSize % 2
            ? (durations[TSize / 2 - 1] + durations[TSize / 2]) / 2
            : durations[TSize / 2];

        return {average, median};
    }

    void Show(const char* name, std::pair<std::chrono::nanoseconds, std::chrono::nanoseconds> measurement)
    {
        auto average = static_cast<float>(measurement.first.count());
        auto median = static_cast<float>(measurement.second.count());
        auto max = std::max(average, median);

        string unit;
        if(1e9 <= max)
        {
            average /= 1e9;
            median /= 1e9;
            unit = "_s";
        }
        else if(1e6 <= max)
        {
            average /= 1e6;
            median /= 1e6;
            unit = "ms";
        }
        else if(1e3 <= max)
        {
            average /= 1e3;
            median /= 1e3;
            unit = "us";
        }
        else
        {
            unit = "ns";
        }
        
        printf("AVG/MED: %8.3f%s/ %8.3f%s, %s\n", average, unit.c_str(), median, unit.c_str(), name);
    }

    template<size_t TSize, typename TFunc>
    void RunBenchmark(const char* name, TFunc&& func)
    {
        auto result = Benchmark::Invoke<TSize>(func);

        Benchmark::Show(name, result);
    }

    #define RUN_BENCHMARK(func) RunBenchmark<1'000>(#func, func)
}
