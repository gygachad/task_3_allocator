#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <vector>

#include "allocator.h"

using namespace std;

void print_map(const map<int, string, less<int>, linear_allocator<pair<const int, string>>>& m)
{
    for (const auto& [key, value] : m) {
        std::cout << '[' << key << "] = " << value << "; ";
    }
    
    std::cout << '\n';
}

template<typename T>
class A
{
public:
    A() {};
    ~A() {};

    template<typename U>
    A(const A<U>& other)
    {
        value = other.value;
    };

    T value = 0;
};

template<typename T>
class B
{
public:
    shared_ptr<A<T>> m_a;

    B() 
    { 
        m_a = make_shared<A<T>>();
    };
    ~B() {};

    template<typename U>
    B(const B<U>& other) 
    {
        m_a = other.m_a;
    };
};

int main() 
{
    /*
    {
        vector<int, linear_allocator<int>> v;

        for (int i = 1; i < 10; i++)
        {
            v.push_back(i);
        }

        for (int i = 0; i < 9; i++)
            cout << v[i];
    }
    */
    while (true)
    {
        {
            map<int, string, less<int>, linear_allocator<pair<const int, string>>> m;

            for (int i = 0; i < 5; i++)
            {
                m[i] = to_string(i);
            }

            for (int i = 0; i < 4; i++)
            {
                m.erase(i);
            }

            //m[11] = "11";

            print_map(m);
        }
    }
    //m.clear();
    
    return 0;
}
