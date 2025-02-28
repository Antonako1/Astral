/*+++
ASTRAL_MACROS.H
Author: Antonako1
Description: Astral header file
Licensed under the MIT License
---*/

#pragma once
#ifndef ASTRAL_MACROS_H
#define ASTRAL_MACROS_H

// Astral Version
#define ASTRAL_VERSION_MAJOR 0
#define ASTRAL_VERSION_MINOR 1
#define ASTRAL_VERSION_PATCH 0
#define ASTRAL_VERSION (ASTRAL_VERSION_MAJOR << 16 | ASTRAL_VERSION_MINOR << 8 | ASTRAL_VERSION_PATCH)

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
    #define ASTRAL_PLATFORM_WINDOWS 1
#elif defined(__linux__) || defined(__unix__)
    #define ASTRAL_PLATFORM_LINUX 1

/*+++
Currently unsupported platforms
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#elif defined(__APPLE__) || defined(__MACH__)
    #define ASTRAL_PLATFORM_APPLE 1
#elif defined(__unix__)
    #define ASTRAL_PLATFORM_UNIX 1
#elif defined(__posix__)
    #define ASTRAL_PLATFORM_POSIX 1
---*/

#else
    #error "Unsupported platform! Please add support for your platform."
#endif

// Compiler detection
#if defined(_MSC_VER)
    #define ASTRAL_COMPILER_MSVC 1
#elif defined(__GNUC__)
    #define ASTRAL_COMPILER_GCC 1
#elif defined(__clang__)
    #define ASTRAL_COMPILER_CLANG 1
#elif defined(__MINGW32__) || defined(__MINGW64__)
    #define ASTRAL_COMPILER_MINGW 1
#else
    #define ASTRAL_COMPILER_UNKNOWN 1
#endif

// Architecture detection
#if defined(__x86_64__) || defined(_M_X64)
    #define ASTRAL_ARCH_X64 1
    #define ASTRAL_ARCH_X86_64 1
    #define ASTRAL_64_BIT 1
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
    #define ASTRAL_ARCH_X86 1
    #define ASTRAL_32_BIT 1
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define ASTRAL_ARCH_ARM64 1
    #define ASTRAL_64_BIT 1
#elif defined(__arm__) || defined(_M_ARM)
    #define ASTRAL_ARCH_ARM 1
    #define ASTRAL_32_BIT 1
#else
    #define ASTRAL_ARCH_UNKNOWN 1
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
// Only on Windows reminder
#ifdef ASTRAL_PLATFORM_WINDOWS
    #define ONLY_ON_WINDOWS_REMINDER(x)
#else
    #define ONLY_ON_WINDOWS_REMINDER(x) \
        message(__FILE__ ":" TOSTRING(__LINE__) ": Reminder: " x " is only implemented on Windows")
#endif

// Only on Linux reminder
#ifdef ASTRAL_PLATFORM_LINUX
    #define ONLY_ON_LINUX_REMINDER(x)
#else
    #define ONLY_ON_LINUX_REMINDER(x) \
        message(__FILE__ ":" TOSTRING(__LINE__) ": Reminder: " x " is only implemented on Linux")
#endif

// Only on Windows and Linux reminder
#if defined(ASTRAL_PLATFORM_WINDOWS) || defined(ASTRAL_PLATFORM_LINUX)
    #define ONLY_ON_WINDOWS_AND_LINUX_REMINDER(x)
#else
    #define ONLY_ON_WINDOWS_AND_LINUX_REMINDER(x) \
        message(__FILE__ ":" TOSTRING(__LINE__) ": Reminder: " x " is only implemented on Windows and Linux")
#endif

#endif // ASTRAL_MACROS_H
