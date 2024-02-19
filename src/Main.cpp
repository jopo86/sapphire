#define SAPPHIRE_NOSYSINFO
#include "Sapphire.h"

#include <chrono>

int main() {
    
    std::cout << "\n";

    Sapphire::Logger logger(true, true, true, false);
    Sapphire::Init(logger);

    return 0;
}
