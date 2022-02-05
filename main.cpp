#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>
#include <chrono>

#include "allocator.h"

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

template<typename T>
void print_map(const T& m)
{
    for (const auto& [key, value] : m) 
        std::cout << key << " " << value << endl;
    
    std::cout << '\n';
}

int factorial(unsigned int n)
{
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int main() 
{
    
    map<int, int, less<int>, linear_allocator<pair<const int, int>>> m1;
    map<int, int> m2;

    for (int i = 0; i < 10; i++)
    {
        m1[i] = factorial(i);
        m2[i] = factorial(i);
    }

    print_map(m1);
    print_map(m2);
    
    /*
    while (true)
    {
        auto t1 = high_resolution_clock::now();
        {
            vector<string, linear_allocator<string>> v;

            for (int i = 0; i < 0x20000; i++)
            {
                v.push_back(to_string(i));
            }

            vector<string, linear_allocator<string>> v2;

            for (int i = 0; i < 0x20000; i++)
            {
                v2.push_back(v[i]);
            }
        }
        auto t2 = high_resolution_clock::now();
        auto ms_int = duration_cast<milliseconds>(t2 - t1);
        std::cout << ms_int.count() << "ms for super allocator\n";
        
        t1 = high_resolution_clock::now();
        {
            vector<string> v;

            for (int i = 0; i < 0x20000; i++)
            {
                v.push_back(to_string(i));
            }

            vector<string> v2;

            for (int i = 0; i < 0x20000; i++)
            {
                v2.push_back(v[i]);
            }
        }
        t2 = high_resolution_clock::now();
        ms_int = duration_cast<milliseconds>(t2 - t1);
        std::cout << ms_int.count() << "ms for default allocator\n";
    }
    
    
    while (true)
    {
        auto t1 = high_resolution_clock::now();
        {
            map<int, string, less<int>, linear_allocator<pair<const int, string>>> m;

            for (int i = 0; i < 0x20000; i++)
            {
                m[i] = to_string(i);
            }

            for (int i = 0; i < 0x20000; i++)
            {
                m[i] = m[i] + to_string(i);
            }

            for (int i = 0; i < 0xffff; i++)
            {
                m.erase(i);
            }

            //print_map(m);
        }
        auto t2 = high_resolution_clock::now();

        auto ms_int = duration_cast<milliseconds>(t2 - t1);

        std::cout << ms_int.count() << "ms for super allocator\n";

        t1 = high_resolution_clock::now();
        {
            map<int, string> m;

            for (int i = 0; i < 0x20000; i++)
            {
                m[i] = to_string(i);
            }

            for (int i = 0; i < 0x20000; i++)
            {
                m[i] = m[i] + to_string(i);
            }

            for (int i = 0; i < 0xffff; i++)
            {
                m.erase(i);
            }

            //print_map(m);
        }
        t2 = high_resolution_clock::now();

        ms_int = duration_cast<milliseconds>(t2 - t1);

        std::cout << ms_int.count() << "ms for default allocator\n";
    }
    */
    return 0;
}
