#include "Core.h"
#include "Logger.h"
#include "DSA.h"
#include "System.h"
#include "Console.h"
#include "FileSystem.h"

Sapphire::Logger* p_logger;
Sapphire::System::SystemInfo sysinfo;
int currentTextColor;

#ifdef OS_WINDOWS
    HANDLE hConsole;
    Sapphire::FileSystem::File dxdiag;
#endif

void Sapphire::Init() 
{
    p_logger = nullptr;
    currentTextColor = Sapphire::Console::Colors::NO_COLOR;
    
    #ifdef OS_WINDOWS
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        
        #ifdef OS_WINDOWS
            sysinfo.setOS(Sapphire::System::OS::WINDOWS);
        #elif defined(OS_LINUX)
            sysinfo.setOS(Sapphire::System::OS::LINUX);
        #elif defined(OS_MAC)
            sysinfo.setOS(Sapphire::System::OS::MAC);
        #else
            sysinfo.setOS(Sapphire::System::OS::UNKNOWN);
        #endif

        #ifdef ARCH_X86
            sysinfo.setARCH(Sapphire::System::ARCH::X86);
        #elif defined(ARCH_X64)
            sysinfo.setARCH(Sapphire::System::ARCH::X64);
        #else
            sysinfo.setARCH(Sapphire::System::ARCH::UNKNOWN);
        #endif

        if (!Sapphire::FileSystem::Exists("dxdiag.txt")) system("dxdiag /t dxdiag.txt");
        dxdiag = Sapphire::FileSystem::File("dxdiag.txt");

        std::vector<std::string> lines = dxdiag.getLines();

        for (int i = 0; i < lines.size(); i++)
        {
            if (lines[i].find("System Information") != std::string::npos)
            {
                i += 2;
                sysinfo.setMachineName(lines[i + 1].substr(lines[i + 1].find(":") + 2));
                sysinfo.setMachineID(lines[i + 2].substr(lines[i + 2].find(":") + 2));
                sysinfo.setOSString(lines[i + 3].substr(lines[i + 3].find(":") + 2));
                sysinfo.setLanguage(lines[i + 4].substr(lines[i + 4].find(":") + 2));
                sysinfo.setManufacturer(lines[i + 5].substr(lines[i + 5].find(":") + 2));
                sysinfo.setModel(lines[i + 6].substr(lines[i + 6].find(":") + 2));
                sysinfo.setBIOS(lines[i + 7].substr(lines[i + 7].find(":") + 2));
                sysinfo.setProcessor(lines[i + 8].substr(lines[i + 8].find(":") + 2));
                sysinfo.setMemory(std::stoi(lines[i + 9].substr(lines[i + 9].find(":") + 2, lines[i + 9].find("MB") - lines[i + 9].find(":") - 2)));
                sysinfo.setAvailableMemory(std::stoi(lines[i + 10].substr(lines[i + 10].find(":") + 2, lines[i + 10].find("MB") - lines[i + 10].find(":") - 2)));
            }
            else if (lines[i].find("Display Devices") != std::string::npos)
            {
                i += 2;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("Card name") != std::string::npos)
                    {
                        Sapphire::System::DisplayDevice device;
                        device.setCardName(lines[i].substr(lines[i].find(":") + 2));
                        device.setManufacturer(lines[i + 1].substr(lines[i + 1].find(":") + 2));
                        device.setChipType(lines[i + 2].substr(lines[i + 2].find(":") + 2));
                        device.setMemory(std::stoi(lines[i + 10].substr(lines[i + 10].find(":") + 2, lines[i + 10].find("MB") - lines[i + 10].find(":") - 2)));
                        sysinfo.addDisplayDevice(device);
                    }
                    i++;
                }
            }
            else if (lines[i].find("Sound Devices") != std::string::npos)
            {
                i += 2;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("Description") != std::string::npos)
                    {
                        Sapphire::System::SoundPlaybackDevice device;
                        device.setName(lines[i].substr(lines[i].find(":") + 2));
                        device.setDefault(lines[i + 1].find("Yes") != std::string::npos || lines[i + 2].find("Yes") != std::string::npos);
                        device.setHardwareID(lines[i + 3].substr(lines[i + 3].find(":") + 2));
                        sysinfo.addSoundPlaybackDevice(device);
                    }
                    i++;
                }
            }
            else if (lines[i].find("Sound Capture Devices") != std::string::npos)
            {
                i += 2;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("Description") != std::string::npos)
                    {
                        Sapphire::System::SoundCaptureDevice device;
                        device.setName(lines[i].substr(lines[i].find(":") + 2));
                        device.setDefault(lines[i + 1].find("Yes") != std::string::npos || lines[i + 2].find("Yes") != std::string::npos);
                        sysinfo.addSoundCaptureDevice(device);
                    }
                    i++;
                }
            }
            else if (lines[i].find("Video Capture Devices") != std::string::npos)
            {
                i += 3;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("FriendlyName") != std::string::npos)
                    {
                        Sapphire::System::VideoCaptureDevice device;
                        device.setName(lines[i].substr(lines[i].find(":") + 2));
                        device.setManufacturer(lines[i + 6].substr(lines[i + 6].find(":") + 2));
                        device.setHardwareID(lines[i + 7].substr(lines[i + 7].find(":") + 2));
                        sysinfo.addVideoCaptureDevice(device);
                    }
                    i++;
                }
            }
            else if (lines[i].find("DirectInput Devices") != std::string::npos)
            {
                i += 2;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("Device Name") != std::string::npos)
                    {
                        Sapphire::System::DirectInputDevice device;
                        device.setName(lines[i].substr(lines[i].find(":") + 2));
                        device.setNumAttached(std::stoi(lines[i + 1].substr(lines[i + 1].find(":") + 2)));
                        sysinfo.addDirectInputDevice(device);
                    }
                    i++;
                }
            }
            else if (lines[i].find("Disk & DVD/CD-ROM Drives") != std::string::npos)
            {
                i += 2;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("Drive") != std::string::npos)
                    {
                        Sapphire::System::Drive drive;
                        drive.setName(lines[i].substr(lines[i].find(":") + 2));
                        drive.setFreeSpace(std::stoi(lines[i + 1].substr(lines[i + 1].find(":") + 2, lines[i + 1].find("GB") - lines[i + 1].find(":") - 2)));
                        drive.setTotalSpace(std::stoi(lines[i + 2].substr(lines[i + 2].find(":") + 2, lines[i + 2].find("GB") - lines[i + 2].find(":") - 2)));
                        drive.setFileSystem(lines[i + 3].substr(lines[i + 3].find(":") + 2));
                        sysinfo.addDrive(drive);
                    }
                    i++;
                }
            }
        }

    #endif
}

std::string Sapphire::Version() 
{
    return std::string(SAPPHIRE_VERSION_MAJOR) + "." + std::string(SAPPHIRE_VERSION_MINOR) + "." + std::string(SAPPHIRE_VERSION_PATCH);
}

Sapphire::Logger::Logger() 
{
    logsEnabled = true;
    warningsEnabled = true;
    errorsEnabled = true;
    throwsEnabled = true;
}

Sapphire::Logger::Logger(bool logsEnabled, bool warningsEnabled, bool errorsEnabled, bool throwsEnabled) 
{
    this->logsEnabled = logsEnabled;
    this->warningsEnabled = warningsEnabled;
    this->errorsEnabled = errorsEnabled;
    this->throwsEnabled = throwsEnabled;
}

void Sapphire::Logger::log(const std::string& message)
{
    logs.push_back(message);
    all.push_back(message);
    if (logsEnabled)
    {
        int color = Sapphire::Console::GetTextColor();
        Sapphire::Console::SetTextColor(Sapphire::Console::Colors::GREEN);
        std::cout << "Sapphire Log: " << message << "\n";
        Sapphire::Console::SetTextColor(color);
    }
}

void Sapphire::Logger::warn(const std::string& message)
{
    warnings.push_back(message);
    all.push_back(message);
    if (warningsEnabled)
    {
        int color = Sapphire::Console::GetTextColor();
        Sapphire::Console::SetTextColor(Sapphire::Console::Colors::YELLOW);
        std::cout << "Sapphire Warning: " << message << "\n";
        Sapphire::Console::SetTextColor(color);
    }
}

void Sapphire::Logger::err(const std::string& message)
{
    errors.push_back(message);
    all.push_back(message);
    if (errorsEnabled)
    {
        int color = Sapphire::Console::GetTextColor();
        Sapphire::Console::SetTextColor(Sapphire::Console::Colors::RED);
        std::cout << "Sapphire Error: " << message << "\n";
        Sapphire::Console::SetTextColor(color);
    }
    if (throwsEnabled) throw std::runtime_error("Sapphire Error: " + message + "\n");
}

bool Sapphire::Logger::isLogsEnabled() 
{
    return logsEnabled;
}

bool Sapphire::Logger::isWarningsEnabled() 
{
    return warningsEnabled;
}

bool Sapphire::Logger::isErrorsEnabled() 
{
    return errorsEnabled;
}

bool Sapphire::Logger::isThrowsEnabled() 
{
    return throwsEnabled;
}

std::vector<std::string> Sapphire::Logger::getLogs() 
{
    return logs;
}

std::vector<std::string> Sapphire::Logger::getWarnings() 
{
    return warnings;
}

std::vector<std::string> Sapphire::Logger::getErrors() 
{
    return errors;
}

std::vector<std::string> Sapphire::Logger::getAllMessages()
{
    return all;
}

void Sapphire::Logger::setLogsEnabled(bool logsEnabled) 
{
    this->logsEnabled = logsEnabled;
}

void Sapphire::Logger::setWarningsEnabled(bool warningsEnabled) 
{
    this->warningsEnabled = warningsEnabled;
}

void Sapphire::Logger::setErrorsEnabled(bool errorsEnabled) 
{
    this->errorsEnabled = errorsEnabled;
}

void Sapphire::Logger::setThrowsEnabled(bool throwsEnabled) 
{
    this->throwsEnabled = throwsEnabled;
}

void Sapphire::Init(Logger& logger) 
{
    p_logger = &logger;
    currentTextColor = Sapphire::Console::Colors::NO_COLOR;

    #ifdef OS_WINDOWS

        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        p_logger->log("initializing... (Windows)");
        
        #ifdef OS_WINDOWS
            sysinfo.setOS(Sapphire::System::OS::WINDOWS);
        #elif defined(OS_LINUX)
            sysinfo.setOS(Sapphire::System::OS::LINUX);
        #elif defined(OS_MAC)
            sysinfo.setOS(Sapphire::System::OS::MAC);
        #else
            sysinfo.setOS(Sapphire::System::OS::UNKNOWN);
        #endif

        #ifdef ARCH_X86
            sysinfo.setARCH(Sapphire::System::ARCH::X86);
        #elif defined(ARCH_X64)
            sysinfo.setARCH(Sapphire::System::ARCH::X64);
        #else
            sysinfo.setARCH(Sapphire::System::ARCH::UNKNOWN);
        #endif

        if (!Sapphire::FileSystem::Exists("dxdiag.txt")) {
            p_logger->log("dxdiag.txt does not exist. Running dxdiag...");
            auto start = std::chrono::high_resolution_clock::now();
            system("dxdiag /t dxdiag.txt");
            auto end = std::chrono::high_resolution_clock::now();
            p_logger->log("dxdiag finished in " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(end - start).count()) + " seconds.");
        }

        p_logger->log("Parsing dxdiag.txt...");
        dxdiag = Sapphire::FileSystem::File("dxdiag.txt");

        std::vector<std::string> lines = dxdiag.getLines();

        for (int i = 0; i < lines.size(); i++)
        {
            if (lines[i].find("System Information") != std::string::npos)
            {
                i += 2;
                sysinfo.setMachineName(lines[i + 1].substr(lines[i + 1].find(":") + 2));
                sysinfo.setMachineID(lines[i + 2].substr(lines[i + 2].find(":") + 2));
                sysinfo.setOSString(lines[i + 3].substr(lines[i + 3].find(":") + 2));
                sysinfo.setLanguage(lines[i + 4].substr(lines[i + 4].find(":") + 2));
                sysinfo.setManufacturer(lines[i + 5].substr(lines[i + 5].find(":") + 2));
                sysinfo.setModel(lines[i + 6].substr(lines[i + 6].find(":") + 2));
                sysinfo.setBIOS(lines[i + 7].substr(lines[i + 7].find(":") + 2));
                sysinfo.setProcessor(lines[i + 8].substr(lines[i + 8].find(":") + 2));
                sysinfo.setMemory(std::stoi(lines[i + 9].substr(lines[i + 9].find(":") + 2, lines[i + 9].find("MB") - lines[i + 9].find(":") - 2)));
                sysinfo.setAvailableMemory(std::stoi(lines[i + 10].substr(lines[i + 10].find(":") + 2, lines[i + 10].find("MB") - lines[i + 10].find(":") - 2)));
            }
            else if (lines[i].find("Display Devices") != std::string::npos)
            {
                i += 2;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("Card name") != std::string::npos)
                    {
                        Sapphire::System::DisplayDevice device;
                        device.setCardName(lines[i].substr(lines[i].find(":") + 2));
                        device.setManufacturer(lines[i + 1].substr(lines[i + 1].find(":") + 2));
                        device.setChipType(lines[i + 2].substr(lines[i + 2].find(":") + 2));
                        device.setMemory(std::stoi(lines[i + 10].substr(lines[i + 10].find(":") + 2, lines[i + 10].find("MB") - lines[i + 10].find(":") - 2)));
                        sysinfo.addDisplayDevice(device);
                    }
                    i++;
                }
            }
            else if (lines[i].find("Sound Devices") != std::string::npos)
            {
                i += 2;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("Description") != std::string::npos)
                    {
                        Sapphire::System::SoundPlaybackDevice device;
                        device.setName(lines[i].substr(lines[i].find(":") + 2));
                        device.setDefault(lines[i + 1].find("Yes") != std::string::npos || lines[i + 2].find("Yes") != std::string::npos);
                        device.setHardwareID(lines[i + 3].substr(lines[i + 3].find(":") + 2));
                        sysinfo.addSoundPlaybackDevice(device);
                    }
                    i++;
                }
            }
            else if (lines[i].find("Sound Capture Devices") != std::string::npos)
            {
                i += 2;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("Description") != std::string::npos)
                    {
                        Sapphire::System::SoundCaptureDevice device;
                        device.setName(lines[i].substr(lines[i].find(":") + 2));
                        device.setDefault(lines[i + 1].find("Yes") != std::string::npos || lines[i + 2].find("Yes") != std::string::npos);
                        sysinfo.addSoundCaptureDevice(device);
                    }
                    i++;
                }
            }
            else if (lines[i].find("Video Capture Devices") != std::string::npos)
            {
                i += 3;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("FriendlyName") != std::string::npos)
                    {
                        Sapphire::System::VideoCaptureDevice device;
                        device.setName(lines[i].substr(lines[i].find(":") + 2));
                        device.setManufacturer(lines[i + 6].substr(lines[i + 6].find(":") + 2));
                        device.setHardwareID(lines[i + 7].substr(lines[i + 7].find(":") + 2));
                        sysinfo.addVideoCaptureDevice(device);
                    }
                    i++;
                }
            }
            else if (lines[i].find("DirectInput Devices") != std::string::npos)
            {
                i += 2;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("Device Name") != std::string::npos)
                    {
                        Sapphire::System::DirectInputDevice device;
                        device.setName(lines[i].substr(lines[i].find(":") + 2));
                        device.setNumAttached(std::stoi(lines[i + 1].substr(lines[i + 1].find(":") + 2)));
                        sysinfo.addDirectInputDevice(device);
                    }
                    i++;
                }
            }
            else if (lines[i].find("Disk & DVD/CD-ROM Drives") != std::string::npos)
            {
                i += 2;
                while (lines[i].find("---") == std::string::npos)
                {
                    if (lines[i].find("Drive") != std::string::npos)
                    {
                        Sapphire::System::Drive drive;
                        drive.setName(lines[i].substr(lines[i].find(":") + 2));
                        drive.setFreeSpace(std::stoi(lines[i + 1].substr(lines[i + 1].find(":") + 2, lines[i + 1].find("GB") - lines[i + 1].find(":") - 2)));
                        drive.setTotalSpace(std::stoi(lines[i + 2].substr(lines[i + 2].find(":") + 2, lines[i + 2].find("GB") - lines[i + 2].find(":") - 2)));
                        drive.setFileSystem(lines[i + 3].substr(lines[i + 3].find(":") + 2));
                        sysinfo.addDrive(drive);
                    }
                    i++;
                }
            }
        }

        p_logger->log("Finished parsing dxdiag.txt.");
        p_logger->log("Sapphire initialized.");

    #endif
}

void Sapphire::SetLogger(Logger& logger) 
{
    p_logger = &logger;
}

Sapphire::Logger& Sapphire::GetLogger() 
{
    return *p_logger;
}

Sapphire::System::DisplayDevice::DisplayDevice() 
{
    cardName = "";
    manufacturer = "";
    chipType = "";
    memory = 0;
}

Sapphire::System::DisplayDevice::DisplayDevice(const std::string& cardName, const std::string& manufacturer, const std::string& chipType, int memory) 
{
    this->cardName = cardName;
    this->manufacturer = manufacturer;
    this->chipType = chipType;
    this->memory = memory;
}

std::string Sapphire::System::DisplayDevice::getCardName() 
{
    return cardName;
}

std::string Sapphire::System::DisplayDevice::getManufacturer() 
{
    return manufacturer;
}

std::string Sapphire::System::DisplayDevice::getChipType() 
{
    return chipType;
}

int Sapphire::System::DisplayDevice::getMemory() 
{
    return memory;
}

void Sapphire::System::DisplayDevice::setCardName(const std::string& cardName) 
{
    this->cardName = cardName;
}

void Sapphire::System::DisplayDevice::setManufacturer(const std::string& manufacturer) 
{
    this->manufacturer = manufacturer;
}

void Sapphire::System::DisplayDevice::setChipType(const std::string& chipType) 
{
    this->chipType = chipType;
}

void Sapphire::System::DisplayDevice::setMemory(int memory) 
{
    this->memory = memory;
}

Sapphire::System::SoundPlaybackDevice::SoundPlaybackDevice()
{
    name = "";
    _default = false;
    hardwareID = "";
}

Sapphire::System::SoundPlaybackDevice::SoundPlaybackDevice(const std::string& name, bool _default, const std::string& hardwareID)
{
    this->name = name;
    this->_default = _default;
    this->hardwareID = hardwareID;
}

std::string Sapphire::System::SoundPlaybackDevice::getName()
{
    return name;
}

bool Sapphire::System::SoundPlaybackDevice::isDefault()
{
    return _default;
}

std::string Sapphire::System::SoundPlaybackDevice::getHardwareID()
{
    return hardwareID;
}

void Sapphire::System::SoundPlaybackDevice::setName(const std::string& name)
{
    this->name = name;
}

void Sapphire::System::SoundPlaybackDevice::setDefault(bool _default)
{
    this->_default = _default;
}

void Sapphire::System::SoundPlaybackDevice::setHardwareID(const std::string& hardwareID)
{
    this->hardwareID = hardwareID;
}

Sapphire::System::SoundCaptureDevice::SoundCaptureDevice()
{
    name = "";
    _default = false;
}

Sapphire::System::SoundCaptureDevice::SoundCaptureDevice(const std::string& name, bool _default)
{
    this->name = name;
    this->_default = _default;
}

std::string Sapphire::System::SoundCaptureDevice::getName()
{
    return name;
}

bool Sapphire::System::SoundCaptureDevice::isDefault()
{
    return _default;
}

void Sapphire::System::SoundCaptureDevice::setName(const std::string& name)
{
    this->name = name;
}

void Sapphire::System::SoundCaptureDevice::setDefault(bool _default)
{
    this->_default = _default;
}

Sapphire::System::VideoCaptureDevice::VideoCaptureDevice()
{
    name = "";
    manufacturer = "";
    hardwareID = "";
}

Sapphire::System::VideoCaptureDevice::VideoCaptureDevice(const std::string& name, const std::string& manufacturer, const std::string& hardwareID)
{
    this->name = name;
    this->manufacturer = manufacturer;
    this->hardwareID = hardwareID;
}

std::string Sapphire::System::VideoCaptureDevice::getName()
{
    return name;
}

std::string Sapphire::System::VideoCaptureDevice::getManufacturer()
{
    return manufacturer;
}

std::string Sapphire::System::VideoCaptureDevice::getHardwareID()
{
    return hardwareID;
}

void Sapphire::System::VideoCaptureDevice::setName(const std::string& name)
{
    this->name = name;
}

void Sapphire::System::VideoCaptureDevice::setManufacturer(const std::string& manufacturer)
{
    this->manufacturer = manufacturer;
}

void Sapphire::System::VideoCaptureDevice::setHardwareID(const std::string& hardwareID)
{
    this->hardwareID = hardwareID;
}

Sapphire::System::DirectInputDevice::DirectInputDevice()
{
    name = "";
    numAttached = 0;
}

Sapphire::System::DirectInputDevice::DirectInputDevice(const std::string& name, int numAttached)
{
    this->name = name;
    this->numAttached = numAttached;
}

std::string Sapphire::System::DirectInputDevice::getName()
{
    return name;
}

int Sapphire::System::DirectInputDevice::getNumAttached()
{
    return numAttached;
}

void Sapphire::System::DirectInputDevice::setName(const std::string& name)
{
    this->name = name;
}

void Sapphire::System::DirectInputDevice::setNumAttached(int numAttached)
{
    this->numAttached = numAttached;
}

Sapphire::System::Drive::Drive()
{
    name = "";
    freeSpace = 0;
    totalSpace = 0;
    std::string fileSystem = "";
}

Sapphire::System::Drive::Drive(const std::string& name, int freeSpace, int totalSpace, const std::string& fileSystem)
{
    this->name = name;
    this->freeSpace = freeSpace;
    this->totalSpace = totalSpace;
    this->fileSystem = fileSystem;
}

std::string Sapphire::System::Drive::getName()
{
    return name;
}

int Sapphire::System::Drive::getFreeSpace()
{
    return freeSpace;
}

int Sapphire::System::Drive::getTotalSpace()
{
    return totalSpace;
}

std::string Sapphire::System::Drive::getFileSystem()
{
    return fileSystem;
}

void Sapphire::System::Drive::setName(const std::string& name)
{
    this->name = name;
}

void Sapphire::System::Drive::setFreeSpace(int freeSpace)
{
    this->freeSpace = freeSpace;
}

void Sapphire::System::Drive::setTotalSpace(int totalSpace)
{
    this->totalSpace = totalSpace;
}

void Sapphire::System::Drive::setFileSystem(const std::string& fileSystem)
{
    this->fileSystem = fileSystem;
}

Sapphire::System::SystemInfo::SystemInfo()
{
    machineName = "";
    machineID = "";
    os = Sapphire::System::OS::UNKNOWN;
    arch = Sapphire::System::ARCH::UNKNOWN;
    osString = "";
    language = "";
    manufacturer = "";
    model = "";
    bios = "";
    processor = "";
    memory = 0;
    availableMemory = 0;
    displayDevices = {};
    soundPlaybackDevices = {};
    soundCaptureDevices = {};
    videoCaptureDevices = {};
    directInputDevices = {};
    drives = {};
}

Sapphire::System::SystemInfo::SystemInfo(const std::string& machineName, const std::string& machineID, Sapphire::System::OS os, Sapphire::System::ARCH arch, const std::string& osString, const std::string& language, const std::string& manufacturer, const std::string& model, const std::string& bios, const std::string& processor, int memory, int availableMemory, std::vector<Sapphire::System::DisplayDevice> displayDevices, std::vector<Sapphire::System::SoundPlaybackDevice> soundPlaybackDevices, std::vector<Sapphire::System::SoundCaptureDevice> soundCaptureDevices, std::vector<Sapphire::System::VideoCaptureDevice> videoCaptureDevices, std::vector<Sapphire::System::DirectInputDevice> directInputDevices, std::vector<Sapphire::System::Drive> drives)
{
    this->machineName = machineName;
    this->machineID = machineID;
    this->os = os;
    this->arch = arch;
    this->osString = osString;
    this->language = language;
    this->manufacturer = manufacturer;
    this->model = model;
    this->bios = bios;
    this->processor = processor;
    this->memory = memory;
    this->availableMemory = availableMemory;
    this->displayDevices = displayDevices;
    this->soundPlaybackDevices = soundPlaybackDevices;
    this->soundCaptureDevices = soundCaptureDevices;
    this->videoCaptureDevices = videoCaptureDevices;
    this->directInputDevices = directInputDevices;
    this->drives = drives;
}

std::string Sapphire::System::SystemInfo::getMachineName()
{
    return machineName;
}

std::string Sapphire::System::SystemInfo::getMachineID()
{
    return machineID;
}

Sapphire::System::OS Sapphire::System::SystemInfo::getOS()
{
    return os;
}

Sapphire::System::ARCH Sapphire::System::SystemInfo::getARCH()
{
    return arch;
}

std::string Sapphire::System::SystemInfo::getOSString()
{
    return osString;
}

std::string Sapphire::System::SystemInfo::getLanguage()
{
    return language;
}

std::string Sapphire::System::SystemInfo::getManufacturer()
{
    return manufacturer;
}

std::string Sapphire::System::SystemInfo::getModel()
{
    return model;
}

std::string Sapphire::System::SystemInfo::getBIOS()
{
    return bios;
}

std::string Sapphire::System::SystemInfo::getProcessor()
{
    return processor;
}

int Sapphire::System::SystemInfo::getMemory()
{
    return memory;
}

int Sapphire::System::SystemInfo::getAvailableMemory()
{
    return availableMemory;
}

std::vector<Sapphire::System::DisplayDevice> Sapphire::System::SystemInfo::getDisplayDevices()
{
    return displayDevices;
}

std::vector<Sapphire::System::SoundPlaybackDevice> Sapphire::System::SystemInfo::getSoundPlaybackDevices()
{
    return soundPlaybackDevices;
}

std::vector<Sapphire::System::SoundCaptureDevice> Sapphire::System::SystemInfo::getSoundCaptureDevices()
{
    return soundCaptureDevices;
}

std::vector<Sapphire::System::VideoCaptureDevice> Sapphire::System::SystemInfo::getVideoCaptureDevices()
{
    return videoCaptureDevices;
}

std::vector<Sapphire::System::DirectInputDevice> Sapphire::System::SystemInfo::getDirectInputDevices()
{
    return directInputDevices;
}

std::vector<Sapphire::System::Drive> Sapphire::System::SystemInfo::getDrives()
{
    return drives;
}

void Sapphire::System::SystemInfo::setMachineName(const std::string& machineName)
{
    this->machineName = machineName;
}

void Sapphire::System::SystemInfo::setMachineID(const std::string& machineID)
{
    this->machineID = machineID;
}

void Sapphire::System::SystemInfo::setOS(Sapphire::System::OS os)
{
    this->os = os;
}

void Sapphire::System::SystemInfo::setARCH(Sapphire::System::ARCH arch)
{
    this->arch = arch;
}

void Sapphire::System::SystemInfo::setOSString(const std::string& osString)
{
    this->osString = osString;
}

void Sapphire::System::SystemInfo::setLanguage(const std::string& language)
{
    this->language = language;
}

void Sapphire::System::SystemInfo::setManufacturer(const std::string& manufacturer)
{
    this->manufacturer = manufacturer;
}

void Sapphire::System::SystemInfo::setModel(const std::string& model)
{
    this->model = model;
}

void Sapphire::System::SystemInfo::setBIOS(const std::string& bios)
{
    this->bios = bios;
}

void Sapphire::System::SystemInfo::setProcessor(const std::string& processor)
{
    this->processor = processor;
}

void Sapphire::System::SystemInfo::setMemory(int memory)
{
    this->memory = memory;
}

void Sapphire::System::SystemInfo::setAvailableMemory(int availableMemory)
{
    this->availableMemory = availableMemory;
}

void Sapphire::System::SystemInfo::setDisplayDevices(const std::vector<Sapphire::System::DisplayDevice>& displayDevices)
{
    this->displayDevices = displayDevices;
}

void Sapphire::System::SystemInfo::addDisplayDevice(const Sapphire::System::DisplayDevice& displayDevice)
{
    displayDevices.push_back(displayDevice);
}

void Sapphire::System::SystemInfo::setSoundPlaybackDevices(const std::vector<Sapphire::System::SoundPlaybackDevice>& soundPlaybackDevices)
{
    this->soundPlaybackDevices = soundPlaybackDevices;
}

void Sapphire::System::SystemInfo::addSoundPlaybackDevice(const Sapphire::System::SoundPlaybackDevice& soundPlaybackDevice)
{
    soundPlaybackDevices.push_back(soundPlaybackDevice);
}

void Sapphire::System::SystemInfo::setSoundCaptureDevices(const std::vector<Sapphire::System::SoundCaptureDevice>& soundCaptureDevices)
{
    this->soundCaptureDevices = soundCaptureDevices;
}

void Sapphire::System::SystemInfo::addSoundCaptureDevice(const Sapphire::System::SoundCaptureDevice& soundCaptureDevice)
{
    soundCaptureDevices.push_back(soundCaptureDevice);
}

void Sapphire::System::SystemInfo::setVideoCaptureDevices(const std::vector<Sapphire::System::VideoCaptureDevice>& videoCaptureDevices)
{
    this->videoCaptureDevices = videoCaptureDevices;
}

void Sapphire::System::SystemInfo::addVideoCaptureDevice(const Sapphire::System::VideoCaptureDevice& videoCaptureDevice)
{
    videoCaptureDevices.push_back(videoCaptureDevice);
}

void Sapphire::System::SystemInfo::setDirectInputDevices(const std::vector<Sapphire::System::DirectInputDevice>& directInputDevices)
{
    this->directInputDevices = directInputDevices;
}

void Sapphire::System::SystemInfo::addDirectInputDevice(const Sapphire::System::DirectInputDevice& directInputDevice)
{
    directInputDevices.push_back(directInputDevice);
}

void Sapphire::System::SystemInfo::setDrives(const std::vector<Sapphire::System::Drive>& drives)
{
    this->drives = drives;
}

void Sapphire::System::SystemInfo::addDrive(const Sapphire::System::Drive& drive)
{
    drives.push_back(drive);
}

Sapphire::System::SystemInfo Sapphire::System::GetSystemInfo()
{
    return sysinfo;
}

std::string Sapphire::System::GetMachineName()
{
    return sysinfo.getMachineName();
}

std::string Sapphire::System::GetMachineID()
{
    return sysinfo.getMachineID();
}

Sapphire::System::OS Sapphire::System::GetOS()
{
    return sysinfo.getOS();
}

Sapphire::System::ARCH Sapphire::System::GetARCH()
{
    return sysinfo.getARCH();
}

std::string Sapphire::System::GetOSString()
{
    return sysinfo.getOSString();
}

std::string Sapphire::System::GetLanguage()
{
    return sysinfo.getLanguage();
}

std::string Sapphire::System::GetManufacturer()
{
    return sysinfo.getManufacturer();
}

std::string Sapphire::System::GetModel()
{
    return sysinfo.getModel();
}

std::string Sapphire::System::GetBIOS()
{
    return sysinfo.getBIOS();
}

std::string Sapphire::System::GetProcessor()
{
    return sysinfo.getProcessor();
}

int Sapphire::System::GetMemory()
{
    return sysinfo.getMemory();
}

int Sapphire::System::GetAvailableMemory()
{
    return sysinfo.getAvailableMemory();
}

std::vector<Sapphire::System::DisplayDevice> Sapphire::System::GetDisplayDevices()
{
    return sysinfo.getDisplayDevices();
}

std::vector<Sapphire::System::SoundPlaybackDevice> Sapphire::System::GetSoundPlaybackDevices()
{
    return sysinfo.getSoundPlaybackDevices();
}

std::vector<Sapphire::System::SoundCaptureDevice> Sapphire::System::GetSoundCaptureDevices()
{
    return sysinfo.getSoundCaptureDevices();
}

std::vector<Sapphire::System::VideoCaptureDevice> Sapphire::System::GetVideoCaptureDevices()
{
    return sysinfo.getVideoCaptureDevices();
}

std::vector<Sapphire::System::DirectInputDevice> Sapphire::System::GetDirectInputDevices()
{
    return sysinfo.getDirectInputDevices();
}

std::vector<Sapphire::System::Drive> Sapphire::System::GetDrives()
{
    return sysinfo.getDrives();
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to create file object, path does not exist: \"" + path + "\"");
        return;
    }

    this->path = path;
    size = 0;
    lineCount = 0;

    refresh();
}

void Sapphire::FileSystem::File::refresh() 
{
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to refresh file object, path does not exist: \"" + path + "\"");
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

    size = std::filesystem::file_size(path);

    istream.close();
}

void Sapphire::FileSystem::File::write(const std::string& contents) 
{
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to write to file (using file object), path does not exist: \"" + path + "\"");
        return;
    }

    ostream.open(path);
    ostream << contents;
    ostream.close(); 

    refresh();
}

void Sapphire::FileSystem::File::writeAppend(const std::string& contents) 
{
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to write to file (using file object), path does not exist: \"" + path + "\"");
        return;
    }

    ostream.open(path, std::ios_base::app);
    ostream << contents;
    ostream.close(); 

    refresh();
}

void Sapphire::FileSystem::File::remove() 
{
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to remove file (using file object), path does not exist: \"" + path + "\"");
        return;
    }

    std::filesystem::remove(path);
}

void Sapphire::FileSystem::File::copy(const std::string& to) 
{
    if (p_logger != nullptr) {
        if (!Exists(path))
        {
            p_logger->err("failed to copy file (using file object), origin path does not exist: \"" + path + "\"");
            return;
        }
        else if (!Exists(to))
        {
            p_logger->err("failed to copy file (using file object), destination path does not exist: \"" + to + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to remove file, path does not exist: \"" + path + "\"");
        return;
    }

    std::filesystem::remove(path);
}

void Sapphire::FileSystem::RemoveDir(const std::string& path)
{
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to remove directory, path does not exist: \"" + path + "\"");
        return;
    }

    std::filesystem::remove_all(path);
}

void Sapphire::FileSystem::CopyFile(const std::string& from, const std::string& to)
{
    if (p_logger != nullptr) {
        if (!Exists(from))
        {
            p_logger->err("failed to copy file, origin path does not exist: \"" + from + "\"");
            return;
        }
        else if (!Exists(to))
        {
            p_logger->err("failed to copy file, destination path does not exist: \"" + to + "\"");
            return;
        }
    }

    std::filesystem::copy_file(from, to);
}

void Sapphire::FileSystem::CopyDir(const std::string& from, const std::string& to)
{
    if (p_logger != nullptr) {
        if (!Exists(from))
        {
            p_logger->err("failed to copy directory, origin path does not exist: \"" + from + "\"");
            return;
        }
        else if (!Exists(to))
        {
            p_logger->err("failed to copy directory, destination path does not exist: \"" + to + "\"");
            return;
        }
    }

    std::filesystem::copy(from, to, std::filesystem::copy_options::recursive);
}

std::vector<std::string> Sapphire::FileSystem::GetFilesAndDirsInDir(const std::string& path)
{
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to iterate through directory (GetFilesAndDirsInDir), path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to iterate through directory (GetFilesAndDirsInDir), path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to iterate through directory (GetFilesInDir), path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to iterate through directory (GetFilesInDir), path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to iterate through directory (GetDirsInDir), path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to iterate through directory (GetFilesAndDirsInDirRecursive), path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to iterate through directory (GetFilesAndDirsInDirRecursive), path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to iterate through directory (GetFilesInDirRecursive), path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to iterate through directory (GetFilesInDirRecursive), path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to iterate through directory (GetDirsInDirRecursive), path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (GetDir(path) != "" && !Exists(GetDir(path))) 
    {
        p_logger->err("failed to write to file, directory does not exist: \"" + GetDir(path) + "\"");
        return File();
    }

    std::ofstream ostream(path);
    ostream << contents;
    ostream.close();

    return File(path);
}

Sapphire::FileSystem::File Sapphire::FileSystem::WriteAppend(const std::string& path, const std::string& contents)
{
    if (p_logger != nullptr) if (!Exists(GetDir(path)))
    {
        p_logger->err("failed to write to file, directory does not exist: \"" + GetDir(path) + "\"");
        return File();
    }

    std::ofstream ostream(path, std::ios_base::app);
    ostream << contents;
    ostream.close();

    return File(path);
}

int Sapphire::FileSystem::CountLines(const std::string& path)
{
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to count lines in file, path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to count lines in file, path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to read file, path does not exist: \"" + path + "\"");
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
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to read file, path does not exist: \"" + path + "\"");
        return {};
    }

    std::ifstream istream(path);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(istream, line)) lines.push_back(line);
    return lines;
}

int Sapphire::FileSystem::GetSize(const std::string& path)
{
    if (p_logger != nullptr) if (!Exists(path))
    {
        p_logger->err("failed to get size of file, path does not exist: \"" + path + "\"");
        return 0;
    }

    return std::filesystem::file_size(path);
}
