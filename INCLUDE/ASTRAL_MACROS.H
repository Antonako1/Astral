/*+++
ASTRAL_MACROS.H
Author: Antonako1
Description: Astral header file
Licensed under the MIT License
---*/

#pragma once
#ifndef ASTRAL_MACROS_H
#define ASTRAL_MACROS_H

#include <ASTRAL_STDINT.H>

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
#if (defined(__x86_64__) || defined(_M_X64) || defined(_M_AMD64)) && sizeof(AS_PTR) == 8
#   define ASTRAL_ARCH_X64 1
#   define ASTRAL_ARCH_X86_64 1
#   define ASTRAL_64_BIT 1
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
#   define ASTRAL_ARCH_X86 1
#   define ASTRAL_ARCH_X86_32 1
#   define ASTRAL_ARCH_I386 1
#   define ASTRAL_ARCH_IA32 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_2__) 
#   define ASTRAL_ARCH_ARM2 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
#   define ASTRAL_ARCH_ARM3 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
#   define ASTRAL_ARCH_ARM4T 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
#   define ASTRAL_ARCH_ARM5 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
#   define ASTRAL_ARCH_ARM6T2 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
#   define ASTRAL_ARCH_ARM6 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#   define ASTRAL_ARCH_ARM7 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#   define ASTRAL_ARCH_ARM7A 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
#   define ASTRAL_ARCH_ARM7R 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_7M__)
#   define ASTRAL_ARCH_ARM7M 1
#   define ASTRAL_32_BIT 1
#elif defined(__ARM_ARCH_7S__)
#   define ASTRAL_ARCH_ARM7S 1
#   define ASTRAL_32_BIT 1

// General ARM architecture
#elif defined(__aarch64__) || defined(_M_ARM64)
#   define ASTRAL_ARCH_ARM64 1
#   define ASTRAL_64_BIT 1
#elif defined(__arm__) || defined(_M_ARM)
#   define ASTRAL_ARCH_ARM 1
#   define ASTRAL_32_BIT 1

#elif defined(mips) || defined(__mips__) || defined(__mips)
#   define ASTRAL_ARCH_MIPS 1
#   define ASTRAL_32_BIT 1
#elif defined(__sh__)
#   define ASTRAL_ARCH_SH 1
#   define ASTRAL_ARCH_SUPERH 1
#   define ASTRAL_32_BIT 1
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
#   define ASTRAL_ARCH_POWERPC 1
#   define ASTRAL_ARCH_PPC 1
#   define ASTRAL_32_BIT 1
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
#   define ASTRAL_ARCH_POWERPC64 1
#   define ASTRAL_ARCH_PPC64 1
#   define ASTRAL_64_BIT 1
#elif defined(__sparc__) || defined(__sparc)
#   define ASTRAL_ARCH_SPARC 1
#   define ASTRAL_32_BIT 1
#elif defined(__m68k__)
#   define ASTRAL_ARCH_M68K 1
#   define ASTRAL_32_BIT 1
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
