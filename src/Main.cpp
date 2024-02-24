#include <iostream>

#include "Core.h"
#include "Logger.h"
#include "System.h"
#include "DSA.h"

int main() {
    
    std::cout << "\n";

    Sapphire::Logger logger(true, true, true, false);
    Sapphire::Init(logger);
    
    Sapphire::DSA::ArrayList<int> list(5);
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list[i] << " ";
    }
    
    std::cout << "\n";

    list.add(1);
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list[i] << " ";
    }

    // !doubling list, fix

    std::cout << "\n";

    list.add(1, 0);
    for (int i = 0; i < list.size(); i++)
    {
        std::cout << list[i] << " ";
    }

    return 0;
}
