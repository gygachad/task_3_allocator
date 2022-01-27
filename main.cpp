#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

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
    //auto v = std::vector<int, Allocator<int>>{};

    Allocator<int> al{};
    al.allocate(3);

    // Create a map of three (strings, int) pairs
    map<string, int> m{ {"CPU", 10}, {"GPU", 15}, {"RAM", 20}, };

    //print_map("1) Initial map: ", m);

    m["CPU"] = 25;  // update an existing value
    m["SSD"] = 30;  // insert a new value
    //print_map("2) Updated map: ", m);

    // using operator[] with non-existent key always performs an insert
    std::cout << "3) m[UPS] = " << m["UPS"] << '\n';
    //print_map("4) Updated map: ", m);

    m.erase("GPU");
    //print_map("5) After erase: ", m);

    m.clear();
    std::cout << std::boolalpha << "8) Map is empty: " << m.empty() << '\n';

    return 0;
}
