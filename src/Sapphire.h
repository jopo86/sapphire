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

namespace Sapphire {

    void Init();
    std::string Version();

    class ErrorHandler {
    public:

        ErrorHandler();
        ErrorHandler(bool logs, bool throws);
        
        void err(const std::string& message);

        void setLogs(bool value);
        void setThrows(bool value);

        bool logsErrors();
        bool throwsErrors();

        std::vector<std::string> getErrors();
        std::string getLastError();

    private:
        bool logs;
        bool throws;
        std::vector<std::string> errors;

    };
    
    void SetErrorHandler(ErrorHandler& handler);
    ErrorHandler& GetErrorHandler();

    namespace System {

        // TODO: functions for getting system information
        // OS, architecture, hardware, etc.

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
