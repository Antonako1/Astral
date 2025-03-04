/*+++
ASTRAL_API.H
Author: Antonako1
Description: API definitions for Astral
Licensed under the MIT License
---*/

#pragma once
#ifndef ASTRAL_API_H
#define ASTRAL_API_H

#include <ASTRAL_MACROS.H>

#if defined(ASTRAL_PLATFORM_WINDOWS)
#   define ASTRAL_EXPORT __declspec(dllexport)
#   define ASTRAL_IMPORT __declspec(dllimport)
#elif defined(ASTRAL_COMPILER_GCC)
#   define ASTRAL_EXPORT __attribute__((visibility("default")))
#   define ASTRAL_IMPORT
#else
#   define ASTRAL_EXPORT
#   define ASTRAL_IMPORT
#endif

// For internal functions, not to be used outside of the library.
#if defined(ASTRAL_DEBUG_ACTIVE)
#   define ASTRAL_EXPORT_INTERNAL ASTRAL_EXPORT
#   define ASTRAL_IMPORT_INTERNAL ASTRAL_IMPORT
#else
#   define ASTRAL_EXPORT_INTERNAL
#   define ASTRAL_IMPORT_INTERNAL
#endif

#endif // ASTRAL_API_H
