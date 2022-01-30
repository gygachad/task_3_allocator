#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "debug.h"
#include "allocator.h"

using namespace std;

/*
void print_map(std::string_view comment, const std::map<std::string, int, less<void>, Allocator<pair<const string, int>>>& m)
{
    std::cout << comment;

    for (const auto& [key, value] : m) {
        std::cout << '[' << key << "] = " << value << "; ";
    }
    
    std::cout << '\n';
}
*/

int main() 
{
    // Create a map of three (strings, int) pairs
    map<int, string, less<int>, Allocator<pair<const int, string>>> m{};

    for (int i = 0; i < 10; i++)
    {
        m[i] = to_string(i);
    }

    m.clear();
    std::cout << std::boolalpha << "8) Map is empty: " << m.empty() << '\n';

    return 0;
}
