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
#elif defined(__linux__)
    #define ASTRAL_PLATFORM_LINUX 1
#elif defined(__APPLE__)
    #define ASTRAL_PLATFORM_APPLE 1
#elif defined(__unix__)
    #define ASTRAL_PLATFORM_UNIX 1
#elif defined(__posix__)
    #define ASTRAL_PLATFORM_POSIX 1
#else
    #error "Unsupported platform! You must define a function for this platform."
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

/*+++
ASTRAL_FUNC_CHOOSE(...) - Selects the correct function based on the platform.
Usage:
    #define MY_EXPORT_FUNCTION ASTRAL_FUNC_CHOOSE(
        WINDOWS_FUNCTION,
        LINUX_FUNCTION
    )

- The first matching function is selected based on the platform.
- If no match is found, compilation **fails** (no default fallback).
- Requires at least **one function per platform**.
---*/

// Macro to choose function based on platform
#define ASTRAL_FUNC_CHOOSE(...) ASTRAL_FUNC_SELECT(__VA_ARGS__)

// Selects the first function that matches a platform, compilation fails if no match
#define ASTRAL_FUNC_SELECT(WIN, LINUX, ...)     \
    ASTRAL_IFDEF(ASTRAL_PLATFORM_WINDOWS, WIN,  \
    ASTRAL_IFDEF(ASTRAL_PLATFORM_LINUX, LINUX,  \
    _ASTRAL_NO_MATCH()                          \
                )                               \
                )

// If no platform is matched, throw a compiler error
#define _ASTRAL_NO_MATCH() static_assert(0, "ASTRAL_FUNC_CHOOSE: No matching function for the current platform!")

// Helper macro for conditional selection
#define ASTRAL_IFDEF(platform, func, next) ASTRAL_IFDEF_IMPL(platform, func, next)
#define ASTRAL_IFDEF_IMPL(platform, func, next) ASTRAL_IFDEF_##platform(func, next)

// Expanding macros based on platform
#if defined(ASTRAL_PLATFORM_WINDOWS)
    #define ASTRAL_IFDEF_ASTRAL_PLATFORM_WINDOWS(func, next) func
#else
    #define ASTRAL_IFDEF_ASTRAL_PLATFORM_WINDOWS(func, next) next
#endif

#if defined(ASTRAL_PLATFORM_LINUX)
    #define ASTRAL_IFDEF_ASTRAL_PLATFORM_LINUX(func, next) func
#else
    #define ASTRAL_IFDEF_ASTRAL_PLATFORM_LINUX(func, next) next
#endif

#if defined(ASTRAL_PLATFORM_APPLE)
    #define ASTRAL_IFDEF_ASTRAL_PLATFORM_APPLE(func, next) func
#else
    #define ASTRAL_IFDEF_ASTRAL_PLATFORM_APPLE(func, next) next
#endif

#if defined(ASTRAL_PLATFORM_UNIX)
    #define ASTRAL_IFDEF_ASTRAL_PLATFORM_UNIX(func, next) func
#else
    #define ASTRAL_IFDEF_ASTRAL_PLATFORM_UNIX(func, next) next
#endif

#if defined(ASTRAL_PLATFORM_POSIX)
    #define ASTRAL_IFDEF_ASTRAL_PLATFORM_POSIX(func, next) func
#else
    #define ASTRAL_IFDEF_ASTRAL_PLATFORM_POSIX(func, next) next
#endif

#endif // ASTRAL_MACROS_H
