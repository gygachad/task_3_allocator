#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>
#include <chrono>

#include "allocator.h"
#include "single_linked_list.h"

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
    
    //single_linked_container<int> int_list;
    single_linked_container<int, linear_allocator<int>> int_list;

    for (int i = 0; i < 10; i++)
    {
        int_list.insert(i);
    }

    int b = int_list[4];

    return 0;
}
