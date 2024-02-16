#ifndef _SAPPHIRE_H
#define _SAPPHIRE_H

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
#endif

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace Sapphire {

    void Init();

    class ErrorHandler {
    public:
        friend class FileSystem::File;

        ErrorHandler();
        ErrorHandler(bool throws, bool logs);

        void setThrows(bool value);
        void setLogs(bool value);

        bool throwsErrors();
        bool logsErrors();

        std::vector<std::string> getErrors();
        std::string getLastError();

    private:
        bool throws;
        bool logs;
        std::vector<std::string> errors;

        void err(const std::string& message);
    };
    
    void SetErrorHandler(ErrorHandler& handler);

    namespace Console {

        namespace Colors {

            extern const int WHITE;
            extern const int RED;
            extern const int YELLOW;
            extern const int GREEN;
            extern const int CYAN;
            extern const int BLUE;
            extern const int MAGENTA;
            extern const int NO_COLOR;
        }

        void Clear();
        void SetTextColor(int color);

    }

    namespace FileSystem {

        class File {
        public:
            File(const std::string& path, bool dynamic = false);

            void refresh();

            std::string getContents();
            std::vector<std::string> getLines();
            std::string getPath();
            std::string getExtension();
            std::string getFilename();
            int getSize();
            int getLineCount();
        };

        File Write(const std::string& path, const std::string& contents);

        std::string Read(const std::string& path);
        std::vector<std::string> ReadLines(const std::string& path);
    }

}

#endif
