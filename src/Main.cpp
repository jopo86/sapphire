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
    
    int nums[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    BubbleSort(nums, sizeof(nums) / sizeof(int));

    for (int n : nums)
    {
        std::cout << n << " ";
    }


    return 0;
}
