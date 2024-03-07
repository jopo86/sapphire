#include <iostream>
#include <string>

#include "Core.h"
#include "Logger.h"
#include "System.h"
#include "DSA.h"

using namespace Sapphire::DSA;

int main() {
    
    std::cout << "\n";

    Sapphire::Logger logger(false, true, true, false);
    Sapphire::Init(logger);
    
    ArrayList<int> nums = { 1, 6, 3, 7, 4, 8, 9, 0, 2, 4, 5, 6, 7, 7, 8, 1, 0, 0, 9 };
    nums.remove(4);
    nums.add(10);

    for (int n : nums)
    {
        std::cout << n << " ";
    }
    std::cout << "\n";

    nums.quickSort();
    for (int n : nums)
    {
        std::cout << n << " ";
    }

    return 0;
}
