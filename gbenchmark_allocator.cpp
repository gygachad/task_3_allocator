#include <string>
#include <benchmark/benchmark.h>
#include "allocator.h"

#include "version.h"

#pragma comment ( lib, "Shlwapi.lib" )

using namespace std;

#define TEST_NUM_COUNT 0x100

template<typename T>
void test_vector(T vec)
{
    for (int i = 0; i < TEST_NUM_COUNT; i++)
    {
        vec.push_back(to_string(i));
    }

    for (int i = 0; i < TEST_NUM_COUNT; i++)
    {
        vec[i] = vec[i] + "test";
    }
}

template<typename T>
void test_map(T m)
{
    for (int i = 0; i < TEST_NUM_COUNT; i++)
    {
        m[i] = to_string(i);
    }

    for (int i = 0; i < TEST_NUM_COUNT; i++)
    {
        m[i] = m[i] + to_string(i);
    }
}

void vector_with_allocator(benchmark::State& state) 
{
    for (auto _ : state)
    {
        vector<string, linear_allocator<string>> v;
        test_vector<vector<string, linear_allocator<string>>>(v);       
    }
}
BENCHMARK(vector_with_allocator);

void vector_default(benchmark::State& state)
{
    for (auto _ : state)
    {
        vector<string> v;
        test_vector<vector<string>>(v);
    }
}
BENCHMARK(vector_default);

void map_default(benchmark::State& state)
{
    for (auto _ : state)
    {
        using map_alloc = map<int, string>;
        map_alloc m;
        test_map<map_alloc>(m);
    }
}
BENCHMARK(map_default);

void map_with_allocator(benchmark::State& state) 
{
    for (auto _ : state)
    {
        using map_alloc = map<int, string, less<int>, linear_allocator<pair<const int, string>>>;
        map_alloc m;

        test_map<map_alloc>(m);
    }
}
BENCHMARK(map_with_allocator);

BENCHMARK_MAIN();