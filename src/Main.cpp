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
    
    int nums[] = { 8, 2, 5, 3, 4, 7, 6, 1 };
    
    MergeSort(nums, sizeof(nums) / sizeof(int));

    for (int n : nums)
    {
        std::cout << n << " ";
    }

    return 0;
}
