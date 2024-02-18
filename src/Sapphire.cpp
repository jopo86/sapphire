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

std::string Sapphire::Version() 
{
    return std::string(SAPPHIRE_VERSION);
}

Sapphire::ErrorHandler::ErrorHandler() 
{
    logs = false;
    throws = false;
}

Sapphire::ErrorHandler::ErrorHandler(bool logs, bool throws) 
{
    this->logs = logs;
    this->throws = throws;
}

void Sapphire::ErrorHandler::err(const std::string& message) 
{
    errors.push_back(message);
    if (logs) 
    {
        int color = Sapphire::Console::GetTextColor();
        Sapphire::Console::SetTextColor(Sapphire::Console::Colors::RED);
        std::cout << "Sapphire Error: " << message << std::endl;
        Sapphire::Console::SetTextColor(color);
    }
    if (throws) throw std::runtime_error("Sapphire Error: " + message);
}

void Sapphire::ErrorHandler::setLogs(bool value) 
{
    logs = value;
}

void Sapphire::ErrorHandler::setThrows(bool value) 
{
    throws = value;
}

bool Sapphire::ErrorHandler::logsErrors() 
{
    return logs;
}

bool Sapphire::ErrorHandler::throwsErrors() 
{
    return throws;
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
        if (color == Sapphire::Console::Colors::NO_COLOR) {
            ResetStyle();
            return;
        }

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
        if (color == Sapphire::Console::Colors::NO_COLOR) {
            ResetStyle();
            return;
        }

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

Sapphire::FileSystem::File::File() 
{
    path = "";
    size = 0;
    lineCount = 0;
}

Sapphire::FileSystem::File::File(const std::string& path) 
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to create file object, path does not exist: \"" + path + "\"");
        return;
    }

    this->path = path;
    size = 0;
    lineCount = 0;

    refresh();
}

void Sapphire::FileSystem::File::refresh() 
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to refresh file object, path does not exist: \"" + path + "\"");
        return;
    }

    istream.open(path);

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
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to write to file (using file object), path does not exist: \"" + path + "\"");
        return;
    }

    ostream.open(path);
    ostream << contents;
    ostream.close(); 

    refresh();
}

void Sapphire::FileSystem::File::writeAppend(const std::string& contents) 
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to write to file (using file object), path does not exist: \"" + path + "\"");
        return;
    }

    ostream.open(path, std::ios_base::app);
    ostream << contents;
    ostream.close(); 

    refresh();
}

void Sapphire::FileSystem::File::remove() 
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to remove file (using file object), path does not exist: \"" + path + "\"");
        return;
    }

    std::filesystem::remove(path);
}

void Sapphire::FileSystem::File::copy(const std::string& to) 
{
    if (errorHandler != nullptr) {
        if (!Exists(path))
        {
            errorHandler->err("failed to copy file (using file object), origin path does not exist: \"" + path + "\"");
            return;
        }
        else if (!Exists(to))
        {
            errorHandler->err("failed to copy file (using file object), destination path does not exist: \"" + to + "\"");
            return;
        }
    }

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

bool Sapphire::FileSystem::Exists(const std::string& path)
{
    return std::filesystem::exists(path);
}

bool Sapphire::FileSystem::IsDir(const std::string& path)
{
    return std::filesystem::is_directory(path);
}

std::string Sapphire::FileSystem::GetExtension(const std::string& path)
{
    int lastDot = -1;

    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (path[i] == '.') 
        {
            lastDot = i;
            break;
        }
    }

    if (lastDot != -1) return path.substr(lastDot + 1);
    else return "";
}

std::string Sapphire::FileSystem::GetFilename(const std::string& path)
{
    int lastDot = -1;
    int lastSlash = -1;

    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (path[i] == '.' && lastDot == -1) lastDot = i;
        if (path[i] == '/' || path[i] == '\\' && lastSlash == -1) lastSlash = i;
        if (lastDot != -1 && lastSlash != -1) break;
    }

    if (lastDot != -1 && lastSlash != -1) return path.substr(lastSlash + 1, lastDot - lastSlash - 1);
    else if (lastSlash != -1) return path.substr(lastSlash + 1);
    else if (lastDot != -1) return path.substr(0, lastDot);
    else return path;
}

std::string Sapphire::FileSystem::GetDir(const std::string& path)
{
    int lastSlash = -1;

    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (path[i] == '/' || path[i] == '\\') 
        {
            lastSlash = i;
            break;
        }
    }

    if (lastSlash != -1) return path.substr(0, lastSlash);
    else return "";
}

void Sapphire::FileSystem::CreateDir(const std::string& path)
{
    std::filesystem::create_directories(path);
}

void Sapphire::FileSystem::RemoveFile(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to remove file, path does not exist: \"" + path + "\"");
        return;
    }

    std::filesystem::remove(path);
}

void Sapphire::FileSystem::RemoveDir(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to remove directory, path does not exist: \"" + path + "\"");
        return;
    }

    std::filesystem::remove_all(path);
}

void Sapphire::FileSystem::CopyFile(const std::string& from, const std::string& to)
{
    if (errorHandler != nullptr) {
        if (!Exists(from))
        {
            errorHandler->err("failed to copy file, origin path does not exist: \"" + from + "\"");
            return;
        }
        else if (!Exists(to))
        {
            errorHandler->err("failed to copy file, destination path does not exist: \"" + to + "\"");
            return;
        }
    }

    std::filesystem::copy_file(from, to);
}

void Sapphire::FileSystem::CopyDir(const std::string& from, const std::string& to)
{
    if (errorHandler != nullptr) {
        if (!Exists(from))
        {
            errorHandler->err("failed to copy directory, origin path does not exist: \"" + from + "\"");
            return;
        }
        else if (!Exists(to))
        {
            errorHandler->err("failed to copy directory, destination path does not exist: \"" + to + "\"");
            return;
        }
    }

    std::filesystem::copy(from, to, std::filesystem::copy_options::recursive);
}

std::vector<std::string> Sapphire::FileSystem::GetFilesAndDirsInDir(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to iterate through directory (GetFilesAndDirsInDir), path does not exist: \"" + path + "\"");
        return {};
    }

    std::vector<std::string> paths;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        paths.push_back(entry.path().string());
    }

    return paths;
}

std::vector<std::string> Sapphire::FileSystem::GetFilesAndDirsInDir(const std::string& path, std::vector<std::string> extensionFilter)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to iterate through directory (GetFilesAndDirsInDir), path does not exist: \"" + path + "\"");
        return {};
    }

    std::vector<std::string> paths;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (std::filesystem::is_directory(entry.path())) paths.push_back(entry.path().string());
        else
        {
            std::string extension = GetExtension(entry.path().string());
            for (std::string filter : extensionFilter)
            {
                if (extension == filter) 
                {
                    paths.push_back(entry.path().string());
                    break;
                }
            }
        }
    }

    return paths;
}

std::vector<std::string> Sapphire::FileSystem::GetFilesInDir(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to iterate through directory (GetFilesInDir), path does not exist: \"" + path + "\"");
        return {};
    }

    std::vector<std::string> paths;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (!std::filesystem::is_directory(entry.path())) paths.push_back(entry.path().string());
    }

    return paths;
}

std::vector<std::string> Sapphire::FileSystem::GetFilesInDir(const std::string& path, std::vector<std::string> extensionFilter)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to iterate through directory (GetFilesInDir), path does not exist: \"" + path + "\"");
        return {};
    }

    std::vector<std::string> paths;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (!std::filesystem::is_directory(entry.path()))
        {
            std::string extension = GetExtension(entry.path().string());
            for (std::string filter : extensionFilter)
            {
                if (extension == filter) 
                {
                    paths.push_back(entry.path().string());
                    break;
                }
            }
        }
    }

    return paths;
}

std::vector<std::string> Sapphire::FileSystem::GetDirsInDir(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to iterate through directory (GetDirsInDir), path does not exist: \"" + path + "\"");
        return {};
    }

    std::vector<std::string> paths;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (std::filesystem::is_directory(entry.path())) paths.push_back(entry.path().string());
    }

    return paths;
}

std::vector<std::string> Sapphire::FileSystem::GetFilesAndDirsInDirRecursive(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to iterate through directory (GetFilesAndDirsInDirRecursive), path does not exist: \"" + path + "\"");
        return {};
    }

    std::vector<std::string> paths;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        paths.push_back(entry.path().string());
    }

    return paths;
}

std::vector<std::string> Sapphire::FileSystem::GetFilesAndDirsInDirRecursive(const std::string& path, std::vector<std::string> extensionFilter)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to iterate through directory (GetFilesAndDirsInDirRecursive), path does not exist: \"" + path + "\"");
        return {};
    }

    std::vector<std::string> paths;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        if (std::filesystem::is_directory(entry.path())) paths.push_back(entry.path().string());
        else
        {
            std::string extension = GetExtension(entry.path().string());
            for (std::string filter : extensionFilter)
            {
                if (extension == filter) 
                {
                    paths.push_back(entry.path().string());
                    break;
                }
            }
        }
    }

    return paths;
}

std::vector<std::string> Sapphire::FileSystem::GetFilesInDirRecursive(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to iterate through directory (GetFilesInDirRecursive), path does not exist: \"" + path + "\"");
        return {};
    }

    std::vector<std::string> paths;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        if (!std::filesystem::is_directory(entry.path())) paths.push_back(entry.path().string());
    }

    return paths;
}

std::vector<std::string> Sapphire::FileSystem::GetFilesInDirRecursive(const std::string& path, std::vector<std::string> extensionFilter)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to iterate through directory (GetFilesInDirRecursive), path does not exist: \"" + path + "\"");
        return {};
    }

    std::vector<std::string> paths;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        if (!std::filesystem::is_directory(entry.path()))
        {
            std::string extension = GetExtension(entry.path().string());
            for (std::string filter : extensionFilter)
            {
                if (extension == filter) 
                {
                    paths.push_back(entry.path().string());
                    break;
                }
            }
        }
    }

    return paths;
}

std::vector<std::string> Sapphire::FileSystem::GetDirsInDirRecursive(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to iterate through directory (GetDirsInDirRecursive), path does not exist: \"" + path + "\"");
        return {};
    }

    std::vector<std::string> paths;

    for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        if (std::filesystem::is_directory(entry.path())) paths.push_back(entry.path().string());
    }

    return paths;
}

Sapphire::FileSystem::File Sapphire::FileSystem::Write(const std::string& path, const std::string& contents)
{
    if (errorHandler != nullptr) if (GetDir(path) != "" && !Exists(GetDir(path))) 
    {
        errorHandler->err("failed to write to file, directory does not exist: \"" + GetDir(path) + "\"");
        return File();
    }

    std::ofstream ostream(path);
    ostream << contents;
    ostream.close();

    return File(path);
}

Sapphire::FileSystem::File Sapphire::FileSystem::WriteAppend(const std::string& path, const std::string& contents)
{
    if (errorHandler != nullptr) if (!Exists(GetDir(path)))
    {
        errorHandler->err("failed to write to file, directory does not exist: \"" + GetDir(path) + "\"");
        return File();
    }

    std::ofstream ostream(path, std::ios_base::app);
    ostream << contents;
    ostream.close();

    return File(path);
}

int Sapphire::FileSystem::CountLines(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to count lines in file, path does not exist: \"" + path + "\"");
        return 0;
    }

    int count = 0;
    std::ifstream istream(path);
    std::string line;
    while (std::getline(istream, line)) count++;
    return count;
}

int Sapphire::FileSystem::CountLinesNoEmpty(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to count lines in file, path does not exist: \"" + path + "\"");
        return 0;
    }

    int count = 0;
    std::ifstream istream(path);
    std::string line;
    while (std::getline(istream, line))
    {
        if (line != "") count++;
    }
    return count;
}

std::string Sapphire::FileSystem::Read(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to read file, path does not exist: \"" + path + "\"");
        return "";
    }

    std::ifstream istream(path);
    std::string contents;
    std::string line;
    while (std::getline(istream, line)) contents += line + "\n";
    return contents;
}

std::vector<std::string> Sapphire::FileSystem::ReadLines(const std::string& path)
{
    if (errorHandler != nullptr) if (!Exists(path))
    {
        errorHandler->err("failed to read file, path does not exist: \"" + path + "\"");
        return {};
    }

    std::ifstream istream(path);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(istream, line)) lines.push_back(line);
    return lines;
}
