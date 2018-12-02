#pragma once



#include <stdbool.h>
#include <stdint.h>



typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;

typedef float f32;
typedef double f64;




typedef enum numstr_StrType
{
    numstr_StrType_Invalid = -1,

    numstr_StrType_BIN = 0,
    numstr_StrType_OCT,
    numstr_StrType_DEC,
    numstr_StrType_HEX,
    numstr_StrType_Float,

    numstr_NumStrTypes
} numstr_StrType;



u32 numstr_str2num(double* num, const char* str, u32 len, numstr_StrType* outStrType);
u32 numstr_num2str(char* buf, u32 bufSize, double x);












































































