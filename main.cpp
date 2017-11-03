#include <iostream>

#include "manipulators.hpp"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;


    std::cout << std::hex << bit::toggle(0u, 0u, 1u) << std::dec << std::endl;


    std::cout <<  (int)(bit::BitField<uint8_t>(0u).set(1u).toggle(3u)) << std::endl;
    return 0;
}
