#pragma once

#include <stdint.h>
#ifndef NULL
#define NULL 0
#endif

#ifndef nullptr
#define	nullptr	NULL
#endif

typedef unsigned char BYTE;
typedef signed char i8;
typedef unsigned char u8;

typedef unsigned short	USHORT;
typedef unsigned short	WCHAR;
typedef unsigned short WORD;
typedef signed short i16;
typedef unsigned short u16;

#if defined(LINUX_CENTOS7)
typedef unsigned int DWORD;
typedef int i32;
typedef unsigned int u32;
typedef unsigned long	ULONG;
typedef long i64;
typedef unsigned long u64;
typedef unsigned long DDWORD;
#else
typedef unsigned long	ULONG;
typedef uint32_t DWORD;
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
typedef uint64_t DDWORD;
#endif

// #define   USE_COLOR32
#ifdef USE_COLOR32
typedef DWORD color_t;
#define COLOR_WHITE    0xFFFFFFFF
#else
// #define COLOR_BLACK                               0x0000
// #define COLOR_WHITE                               0xFFFF
// #define COLOR_RED                                 0xF800
// #define COLOR_BLUE                                0x001F
// #define COLOR_GREEN                               0x07E0
// #define COLOR_YELLOW                              0xFFE0
typedef unsigned short color_t;
#endif

#define	yMAX(a,b)	(a>b?a:b)
#define	yMIN(a,b)	(a>b?b:a)










