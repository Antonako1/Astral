/*+++
ASTRAL_STDINT.H
Author: Antonako1
Description: Astral standard integer types
Licensed under the MIT License
---*/

#pragma once
#ifndef ASTRAL_STDINT_H
#define ASTRAL_STDINT_H

#include <ASTRAL_MACROS.H>

/*+++
Type definitions

U0: void
U8: unsigned char
U16: unsigned short
U32: unsigned int
U64: unsigned long long
I8: signed char
I16: signed short
I32: signed int
I64: signed long long
F32: float
F64: double
BOOLEAN: _Bool
TRUE: 1
FALSE: 0
---*/
typedef void                AS_U0;
typedef unsigned char       AS_U8;
typedef unsigned short      AS_U16;
typedef unsigned int        AS_U32;
typedef unsigned long long  AS_U64;
typedef signed char         AS_I8;
typedef signed short        AS_I16;
typedef signed int          AS_I32;
typedef signed long long    AS_I64;
typedef float               AS_F32;
typedef double              AS_F64;
#ifdef __cplusplus
#   define NULLPTR              nullptr
#   define AS_BOOLEAN           bool
#else
#   define NULLPTR              ((void *)0)
#   define AS_BOOLEAN           _Bool
#endif
#define TRUE                1
#define FALSE               0

// Pointer size
#ifdef ASTRAL_64_BIT
typedef AS_U64 AS_PTR;
#else // Defaults to 32-bit
typedef AS_U32 AS_PTR;
#endif

/*+++
Min-Max definitions
---*/
#ifdef ASTRAL_PLATFORM_WINDOWS
#   define I8_MIN              (-127i8 - 1)
#   define I16_MIN             (-32767i16 - 1)
#   define I32_MIN             (-2147483647i32 - 1)
#   define I64_MIN             (-9223372036854775807i64)
#   define I8_MAX              127i8
#   define I16_MAX             32767i16
#   define I32_MAX             2147483647i32
#   define I64_MAX             9223372036854775807i64
#   define U8_MAX              0xffui8
#   define U16_MAX             0xffffui16
#   define U32_MAX             0xffffffffui32
#   define U64_MAX             0xffffffffffffffffui64
#   define F32_MAX             3.402823466e+38F
#   define F64_MAX             1.7976931348623158e+308
#elif ASTRAL_PLATFORM_LINUX
#   define I8_MIN              (-128)
#   define I16_MIN             (-32767-1)
#   define I32_MIN             (-2147483647-1)
#   define I64_MIN             (-9223372036854775807-1)
#   define I8_MAX              (127)
#   define I16_MAX             (32767)
#   define I32_MAX             (2147483647)
#   define I64_MAX             (9223372036854775807)
#   define U8_MAX              0xff
#   define U16_MAX             0xffff
#   define U32_MAX             0xffffffff
#   define U64_MAX             0xffffffffffffffff
#   define F32_MAX             3.402823466e+38F
#   define F64_MAX             1.7976931348623158e+308
#else // Defaults to Windows
#   define I8_MIN              (-127i8 - 1)
#   define I16_MIN             (-32767i16 - 1)
#   define I32_MIN             (-2147483647i32 - 1)
#   define I64_MIN             (-9223372036854775807i64)
#   define I8_MAX              127i8
#   define I16_MAX             32767i16
#   define I32_MAX             2147483647i32
#   define I64_MAX             9223372036854775807i64
#   define U8_MAX              0xffui8
#   define U16_MAX             0xffffui16
#   define U32_MAX             0xffffffffui32
#   define U64_MAX             0xffffffffffffffffui64
#   define F32_MAX             3.402823466e+38F
#   define F64_MAX             1.7976931348623158e+308
#endif // ASTRAL_PLATFORM_WINDOWS
#endif // ASTRAL_STDINT_H
