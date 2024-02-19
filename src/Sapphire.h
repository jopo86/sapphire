#ifndef _SAPPHIRE_H
#define _SAPPHIRE_H

#define SAPPHIRE_VERSION "0.0.0-dev"

#if defined(__LP64__) || defined(_LP64) || defined(__amd64__) || defined(__x86_64__) || defined(_M_X64) || defined(_WIN64) || defined(__ia64__) || defined(_M_IA64) || defined(__aarch64__) || defined(__powerpc64__) || defined(__ppc64__) || defined(__PPC64__) || defined(__mips64__) || defined(__mips64) || defined(__mips64) || defined(__sparc64__) || defined(__arch64__)
	#define ARCH_64
    #define ARCH_X64
#elif defined(__i386__) || defined(_M_IX86) || defined(__arm__) || defined(__mips__) || defined(__mips) || defined(__sparc__) || defined(__PPC__) || defined(__ppc__) || defined(__powerpc__) || defined(__powerpc) || defined(__ppc64__) || defined(__PPC64__) || defined(__ppc64) || defined(__PPC64) || defined(__mip) || defined(__mips) || defined(__mips__)
	#define ARCH_32
    #define ARCH_X86
#else
	#define ARCH_UNKNOWN
#endif

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
	#define OS_WINDOWS
#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
	#define OS_LINUX
#elif defined(__APPLE__) || defined(__MACH__)
	#define OS_MAC
#else
	#define OS_UNKNOWN
#endif

#ifdef OS_WINDOWS
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #undef CopyFile
#endif

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <chrono>

typedef unsigned int uint;
typedef char byte;
typedef unsigned char ubyte;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;

namespace Sapphire {

    void Init();
    std::string Version();

    class Logger {
    public:

        Logger();
        Logger(bool logsEnabled, bool warningsEnabled, bool errorsEnabled, bool throwsEnabled);
        
        void log(const std::string& message);
        void warn(const std::string& message);
        void err(const std::string& message);

        bool isLogsEnabled();
        bool isWarningsEnabled();
        bool isErrorsEnabled();
        bool isThrowsEnabled();

        std::vector<std::string> getLogs();
        std::vector<std::string> getWarnings();
        std::vector<std::string> getErrors();
        std::vector<std::string> getAllMessages();

        void setLogsEnabled(bool value);
        void setWarningsEnabled(bool value);
        void setErrorsEnabled(bool value);
        void setThrowsEnabled(bool value);

    private:
        bool logsEnabled;
        bool warningsEnabled;
        bool errorsEnabled;
        bool throwsEnabled;
        std::vector<std::string> logs;
        std::vector<std::string> warnings;
        std::vector<std::string> errors;
        std::vector<std::string> all;
    };
    
    void Init(Logger& logger);
    void SetLogger(Logger& logger);
    Logger& GetLogger();


    namespace System {

        enum class OS 
        {
            WINDOWS,
            LINUX,
            MAC,
            UNKNOWN
        };

        enum class ARCH 
        {
            X86,
            X64,
            UNKNOWN
        };

        class DisplayDevice
        {
        public:
            DisplayDevice();
            DisplayDevice(const std::string& cardName, const std::string& manufacturer, const std::string& chipType, int memory);

            std::string getCardName();
            std::string getManufacturer();
            std::string getChipType();
            int getMemory();

            void setCardName(const std::string& value);
            void setManufacturer(const std::string& value);
            void setChipType(const std::string& value);
            void setMemory(int value);

        private:
            std::string cardName;
            std::string manufacturer;
            std::string chipType;
            int memory;
        };

        class SoundPlaybackDevice
        {
        public:
            SoundPlaybackDevice();
            SoundPlaybackDevice(const std::string& name, bool _default, const std::string& hardwareID);

            std::string getName();
            bool isDefault();
            std::string getHardwareID();

            void setName(const std::string& value);
            void setDefault(bool value);
            void setHardwareID(const std::string& value);

        private:
            std::string name;
            bool _default;
            std::string hardwareID;
        };

        class SoundCaptureDevice
        {
        public:
            SoundCaptureDevice();
            SoundCaptureDevice(const std::string& name, bool _default);

            std::string getName();
            bool isDefault();

            void setName(const std::string& value);
            void setDefault(bool value);

        private:
            std::string name;
            bool _default;
        };

        class VideoCaptureDevice
        {
        public:
            VideoCaptureDevice();
            VideoCaptureDevice(const std::string& name, const std::string& manufacturer, const std::string& hardwareID);

            std::string getName();
            std::string getManufacturer();
            std::string getHardwareID();

            void setName(const std::string& value);
            void setManufacturer(const std::string& value);
            void setHardwareID(const std::string& value);

        private:
            std::string name;
            std::string manufacturer;
            std::string hardwareID;
        };

        class DirectInputDevice
        {
        public:
            DirectInputDevice();
            DirectInputDevice(const std::string& name, int numAttached);

            std::string getName();
            int getNumAttached();

            void setName(const std::string& value);
            void setNumAttached(int value);

        private:
            std::string name;
            int numAttached;
        };

        class Drive
        {
        public:
            Drive();
            Drive(const std::string& name, int freeSpace, int totalSpace, const std::string& fileSystem);

            std::string getName();
            int getFreeSpace();
            int getTotalSpace();
            std::string getFileSystem();

            void setName(const std::string& value);
            void setFreeSpace(int value);
            void setTotalSpace(int value);
            void setFileSystem(const std::string& value);

        private:
            std::string name;
            int freeSpace;
            int totalSpace;
            std::string fileSystem;
        };

        class SystemInfo
        {
        public:
            SystemInfo();
            SystemInfo(const std::string& machineName, const std::string& machineID, OS os, ARCH arch, const std::string& osString, const std::string& language, const std::string& manufacturer, const std::string& model, const std::string& bios, const std::string& processor, int memory, int availableMemory, std::vector<DisplayDevice> displayDevices, std::vector<SoundPlaybackDevice> soundPlaybackDevices, std::vector<SoundCaptureDevice> soundCaptureDevices, std::vector<VideoCaptureDevice> videoCaptureDevices, std::vector<DirectInputDevice> directInputDevices, std::vector<Drive> drives);

            std::string getMachineName();
            std::string getMachineID();
            OS getOS();
            ARCH getARCH();
            std::string getOSString();
            std::string getLanguage();
            std::string getManufacturer();
            std::string getModel();
            std::string getBIOS();
            std::string getProcessor();
            int getMemory();
            int getAvailableMemory();
            std::vector<DisplayDevice> getDisplayDevices();
            std::vector<SoundPlaybackDevice> getSoundPlaybackDevices();
            std::vector<SoundCaptureDevice> getSoundCaptureDevices();
            std::vector<VideoCaptureDevice> getVideoCaptureDevices();
            std::vector<DirectInputDevice> getDirectInputDevices();
            std::vector<Drive> getDrives();

            void setMachineName(const std::string& value);
            void setMachineID(const std::string& value);
            void setOS(OS value);
            void setARCH(ARCH value);
            void setOSString(const std::string& value);
            void setLanguage(const std::string& value);
            void setManufacturer(const std::string& value);
            void setModel(const std::string& value);
            void setBIOS(const std::string& value);
            void setProcessor(const std::string& value);
            void setMemory(int value);
            void setAvailableMemory(int value);
            void setDisplayDevices(const std::vector<DisplayDevice>& value);
            void addDisplayDevice(const DisplayDevice& value);
            void setSoundPlaybackDevices(const std::vector<SoundPlaybackDevice>& value);
            void addSoundPlaybackDevice(const SoundPlaybackDevice& value);
            void setSoundCaptureDevices(const std::vector<SoundCaptureDevice>& value);
            void addSoundCaptureDevice(const SoundCaptureDevice& value);
            void setVideoCaptureDevices(const std::vector<VideoCaptureDevice>& value);
            void addVideoCaptureDevice(const VideoCaptureDevice& value);
            void setDirectInputDevices(const std::vector<DirectInputDevice>& value);
            void addDirectInputDevice(const DirectInputDevice& value);
            void setDrives(const std::vector<Drive>& value);
            void addDrive(const Drive& value);

        private:
            std::string machineName;
            std::string machineID;
            OS os;
            ARCH arch;
            std::string osString;
            std::string language;
            std::string manufacturer;
            std::string model;
            std::string bios;
            std::string processor;
            int memory;
            int availableMemory;
            std::vector<DisplayDevice> displayDevices;
            std::vector<SoundPlaybackDevice> soundPlaybackDevices;
            std::vector<SoundCaptureDevice> soundCaptureDevices;
            std::vector<VideoCaptureDevice> videoCaptureDevices;
            std::vector<DirectInputDevice> directInputDevices;
            std::vector<Drive> drives;
        };

        SystemInfo GetSystemInfo();
        std::string GetMachineName();
        std::string GetMachineID();
        OS GetOS();
        ARCH GetARCH();
        std::string GetOSString();
        std::string GetLanguage();
        std::string GetManufacturer();
        std::string GetModel();
        std::string GetBIOS();
        std::string GetProcessor();
        int GetMemory();
        int GetAvailableMemory();
        std::vector<DisplayDevice> GetDisplayDevices();
        std::vector<SoundPlaybackDevice> GetSoundPlaybackDevices();
        std::vector<SoundCaptureDevice> GetSoundCaptureDevices();
        std::vector<VideoCaptureDevice> GetVideoCaptureDevices();
        std::vector<DirectInputDevice> GetDirectInputDevices();
        std::vector<Drive> GetDrives();

    }

    namespace Console {

        namespace Colors {

            #ifdef OS_WINDOWS
                static int WHITE = 7;
                static int RED = 12;
                static int YELLOW = 6;
                static int GREEN = 10;
                static int CYAN = 11;
                static int BLUE = 3;
                static int MAGENTA = 13;
            #else
                static int WHITE = 37;
                static int RED = 31;
                static int YELLOW = 33;
                static int GREEN = 32;
                static int CYAN = 36;
                static int BLUE = 34;
                static int MAGENTA = 35;
            #endif

            static int NO_COLOR = -1;
        }

        void Clear();
        void SetTextColor(int color);
        int GetTextColor();
        void SetItalic();
        void SetUnderline();
        void ResetStyle();
    }

    namespace FileSystem {

        class File {
        public:
            File();
            File(const std::string& path);

            void refresh();
            void write(const std::string& contents);
            void writeAppend(const std::string& contents);
            void remove();
            void copy(const std::string& to);

            std::string getContents();
            std::vector<std::string> getLines();
            std::string getPath();
            std::string getExtension();
            std::string getFilename();
            int getSize();
            int getLineCount();


        private:
            std::ifstream istream;
            std::ofstream ostream;

            std::string path;
            std::string contents;
            std::vector<std::string> lines;
            std::string extension;
            std::string filename;
            int size;
            int lineCount;
        };

        bool Exists(const std::string& path);
        bool IsDir(const std::string& path);
        std::string GetExtension(const std::string& path);
        std::string GetFilename(const std::string& path);
        std::string GetDir(const std::string& path);
        void CreateDir(const std::string& path);
        void RemoveFile(const std::string& path);
        void RemoveDir(const std::string& path);
        void CopyFile(const std::string& from, const std::string& to);
        void CopyDir(const std::string& from, const std::string& to);

        std::vector<std::string> GetFilesAndDirsInDir(const std::string& path);
        std::vector<std::string> GetFilesAndDirsInDir(const std::string& path, std::vector<std::string> extensionFilter);
        std::vector<std::string> GetFilesInDir(const std::string& path);
        std::vector<std::string> GetFilesInDir(const std::string& path, std::vector<std::string> extensionFilter);
        std::vector<std::string> GetDirsInDir(const std::string& path);
        std::vector<std::string> GetFilesAndDirsInDirRecursive(const std::string& path);
        std::vector<std::string> GetFilesAndDirsInDirRecursive(const std::string& path, std::vector<std::string> extensionFilter);
        std::vector<std::string> GetFilesInDirRecursive(const std::string& path);
        std::vector<std::string> GetFilesInDirRecursive(const std::string& path, std::vector<std::string> extensionFilter);
        std::vector<std::string> GetDirsInDirRecursive(const std::string& path);

        File Write(const std::string& path, const std::string& contents);
        File WriteAppend(const std::string& path, const std::string& contents);

        int CountLines(const std::string& path);
        int CountLinesNoEmpty(const std::string& path);

        std::string Read(const std::string& path);
        std::vector<std::string> ReadLines(const std::string& path);
    }

}

#endif
