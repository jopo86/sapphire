#include <iostream>
#include <string>

#include "Core.h"
#include "Logger.h"
#include "System.h"
#include "DSA.h"

using namespace Sapphire::DSA;

int main() {
    
    std::cout << "\n";

    Sapphire::Logger logger(true, true, true, false);
    Sapphire::Init(logger, false);
    
    ArrayList<int> nums = { 1, 2, 3 };
    std::cout << nums[3];

    return 0;
}
