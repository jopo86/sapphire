#include "Sapphire.h"

Sapphire::ErrorHandler* errorHandler;
int currentTextColor;

#ifdef OS_WINDOWS
    HANDLE hConsole;
#endif

void Sapphire::Init() 
{
    errorHandler = nullptr;
    currentTextColor = Sapphire::Console::Colors::NO_COLOR;
    
    #ifdef OS_WINDOWS
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
}

Sapphire::ErrorHandler::ErrorHandler() 
{
    throws = false;
    logs = false;
}

Sapphire::ErrorHandler::ErrorHandler(bool throws, bool logs) 
{
    this->throws = throws;
    this->logs = logs;
}

void Sapphire::ErrorHandler::err(const std::string& message) 
{
    errors.push_back(message);
    if (logs) std::cout << message;
    if (throws) throw std::runtime_error(message);
}

void Sapphire::ErrorHandler::setThrows(bool value) 
{
    throws = value;
}

void Sapphire::ErrorHandler::setLogs(bool value) 
{
    logs = value;
}

bool Sapphire::ErrorHandler::throwsErrors() 
{
    return throws;
}

bool Sapphire::ErrorHandler::logsErrors() 
{
    return logs;
}

std::vector<std::string> Sapphire::ErrorHandler::getErrors()
{
    return errors;
}

std::string Sapphire::ErrorHandler::getLastError() 
{
    return errors.back();
}

void Sapphire::SetErrorHandler(ErrorHandler& handler) 
{
    errorHandler = &handler;
}

Sapphire::ErrorHandler& Sapphire::GetErrorHandler() 
{
    return *errorHandler;
}

#ifdef OS_WINDOWS
    void Sapphire::Console::Clear() 
    {
        system("cls");
    }

    void Sapphire::Console::SetTextColor(int color)
    {
        if (currentTextColor == color) return;
        if (currentTextColor == Sapphire::Console::Colors::NO_COLOR) ResetStyle();

        SetConsoleTextAttribute(hConsole, color);
        currentTextColor = color;
    }

    void Sapphire::Console::ResetStyle()
    {
        SetConsoleTextAttribute(hConsole, Sapphire::Console::Colors::WHITE);
        currentTextColor = Sapphire::Console::Colors::WHITE;
    }

#else
    void Sapphire::Console::Clear() 
    {
        system("clear");
    }

    void Sapphire::Console::SetTextColor(int color) 
    {
        if (currentTextColor == color) return;
        if (currentTextColor == Sapphire::Console::Colors::NO_COLOR) ResetStyle();

        std::cout << "\033[" << color << "m";
        currentTextColor = color;
    }

    void Sapphire::Console::ResetStyle() 
    {
        std::cout << "\033[0m";
        currentTextColor = Sapphire::Console::Colors::NO_COLOR;
    }

#endif

int Sapphire::Console::GetTextColor()
{
    return currentTextColor;
}

void Sapphire::Console::SetItalic()
{
    std::cout << "\033[3m";
}

void Sapphire::Console::SetUnderline()
{
    std::cout << "\033[4m";
}

Sapphire::FileSystem::File::File(const std::string& path) 
{
    this->path = path;
    size = 0;
    lineCount = 0;

    refresh();
}

void Sapphire::FileSystem::File::refresh() 
{
    istream.open(path);

    if (!istream.is_open() && errorHandler != nullptr) 
    {
        errorHandler->err("Sapphire error: Failed to open file: " + path);
        return;
    }

    contents = "";
    lines.clear();
    extension = "";
    filename = "";
    size = 0;
    lineCount = 0;

    std::string line;
    while (!istream.eof()) 
    {
        std::getline(istream, line);
        contents += line + "\n";
        lines.push_back(line);
        lineCount++;
    }

    extension = Sapphire::FileSystem::GetExtension(path);
    filename = Sapphire::FileSystem::GetFilename(path);

    size = contents.size();

    istream.close();
}

void Sapphire::FileSystem::File::write(const std::string& contents) 
{
    ostream.open(path);
    ostream << contents;
    ostream.close(); 

    refresh();
}

void Sapphire::FileSystem::File::writeAppend(const std::string& contents) 
{
    ostream.open(path, std::ios_base::app);
    ostream << contents;
    ostream.close(); 

    refresh();
}

void Sapphire::FileSystem::File::remove() 
{
    std::filesystem::remove(path);
}

void Sapphire::FileSystem::File::move(const std::string& to) 
{
    copy(to);
    remove();
    path = to;
    refresh();
}

void Sapphire::FileSystem::File::copy(const std::string& to) 
{
    std::filesystem::copy_file(path, to);
}

std::string Sapphire::FileSystem::File::getContents() 
{
    return contents;
}

std::vector<std::string> Sapphire::FileSystem::File::getLines() 
{
    return lines;
}

std::string Sapphire::FileSystem::File::getPath() 
{
    return path;
}

std::string Sapphire::FileSystem::File::getExtension() 
{
    return extension;
}

std::string Sapphire::FileSystem::File::getFilename() 
{
    return filename;
}

int Sapphire::FileSystem::File::getSize() 
{
    return size;
}

int Sapphire::FileSystem::File::getLineCount() 
{
    return lineCount;
}


