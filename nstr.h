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




typedef enum NSTR_StrType
{
    NSTR_StrType_Invalid = -1,

    NSTR_StrType_BIN = 0,
    NSTR_StrType_OCT,
    NSTR_StrType_DEC,
    NSTR_StrType_HEX,
    NSTR_StrType_FLT,

    NSTR_NumStrTypes
} NSTR_StrType;



u32 NSTR_str2num(double* num, const char* str, u32 len, NSTR_StrType* outStrType);
u32 NSTR_num2str(char* buf, u32 bufSize, double x);












































































