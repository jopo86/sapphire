#pragma once

#define SAPPHIRE_VERSION_MAJOR 0
#define SAPPHIRE_VERSION_MINOR 0
#define SAPPHIRE_VERSION_PATCH 0

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

#include <string>

#include "Logger.h"

typedef unsigned int uint;
typedef char byte;
typedef unsigned char ubyte;
typedef unsigned short ushort;
typedef unsigned long ulong;
typedef unsigned long long ulonglong;

/*
    @brief Sapphire is a C++ library that provides a large set of tools for developers.
    Every Sapphire function is under this namespace.
 */
namespace Sapphire {

    /*
        @brief Returns the version of the library
        @return The version of the library in the format "MAJOR.MINOR.PATCH".
      */
    std::string Version();

    /*
        @brief Initializes the library.
        Must be called before using any other function (except creating a Logger object).
        @param getSysInfo Whether to fetch system info.
        This can take a while, especially if it's the first time the program is being ran.
        Enter false if you don't need to access system info.
        True by default.
     */
    void Init(bool getSysInfo = true);

    /*
        @brief Initializes the library with the specified logger.
        @param logger The logger to use.
        @param getSysInfo Whether to fetch system info.
        This can take a while, especially if it's the first time the program is being ran.
        Enter false if you don't need to access system info.
        True by default.
     */
    void Init(Logger& logger, bool getSysInfo = true);

    /*
        @brief Sets the logger to use.
        @param logger The logger to use.
     */
    void SetLogger(Logger& logger);

    /*
        @brief Gets the logger being used.
        @return The logger being used.
     */
    Logger& GetLogger();
}
