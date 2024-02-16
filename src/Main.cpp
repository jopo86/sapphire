#include "Sapphire.h"

int main() {
    
    Sapphire::Init();

    Sapphire::ErrorHandler errorHandler(true, false);
    Sapphire::SetErrorHandler(errorHandler);

    Sapphire::Console::SetTextColor(Sapphire::Console::Colors::RED);
    Sapphire::Console::SetUnderline();
    std::cout << "Hello, World!" << std::endl;
    Sapphire::Console::ResetStyle();

    return 0;
}
