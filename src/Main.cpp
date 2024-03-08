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
    
    

    return 0;
}
