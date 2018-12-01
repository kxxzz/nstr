#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>

#include "numstr.h"






u32 numstr_str2num(double* num, const char* str, numstr_StrType* outStrType)
{
    numstr_StrType strType = numstr_StrType_DEC;
    u32 off = 0;
    if ((str[off] < '0') || (str[off] > '9'))
    {
        *num = NAN;
        if (outStrType)
        {
            *outStrType = numstr_StrType_Invalid;
        }
        return off;
    }
    bool floatDoted = false;
    if ('0' == str[off])
    {
        ++off;
        if      ((('b' == str[off]) || ('B' == str[off])) && str[off + 1])
        {
            ++off;
            strType = numstr_StrType_BIN;
        }
        else if ((('o' == str[off]) || ('O' == str[off])) && str[off + 1])
        {
            ++off;
            strType = numstr_StrType_OCT;
        }
        else if ((('x' == str[off]) || ('X' == str[off])) && str[off + 1])
        {
            ++off;
            strType = numstr_StrType_HEX;
        }
        else if ('.' == str[off])
        {
            ++off;
            strType = numstr_StrType_Float;
            floatDoted = true;
        }
        else
        {
            strType = numstr_StrType_OCT;
        }
    }
    for (;;)
    {
        if (!str[off])
        {
            break;
        }
        if (numstr_StrType_BIN == strType)
        {
            if (('0' > str[off]) || ('1' < str[off]))
            {
                break;
            }
        }
        else if (numstr_StrType_OCT == strType)
        {
            if (('0' > str[off]) || ('7' < str[off]))
            {
                if ((1 == off) && ('0' == str[off - 1]))
                {
                    strType = numstr_StrType_DEC;
                }
                break;
            }
        }
        else if (numstr_StrType_DEC == strType)
        {
            if (!floatDoted && ('.' == str[off]))
            {
                strType = numstr_StrType_Float;
                floatDoted = true;
            }
            else if (('0' > str[off]) || ('9' < str[off]))
            {
                break;
            }
        }
        else if (numstr_StrType_HEX == strType)
        {
            if ((('0' > str[off]) || ('9' < str[off])) &&
                (('a' > str[off]) || ('f' < str[off])) &&
                (('A' > str[off]) || ('F' < str[off])))
            {
                break;
            }
        }
        else if (numstr_StrType_Float == strType)
        {
            if (!floatDoted && ('.' == str[off]))
            {
                floatDoted = true;
            }
            if (('0' > str[off]) || ('9' < str[off]))
            {
                break;
            }
        }
        else
        {
            break;
        }
        ++off;
    }
    if (numstr_StrType_Invalid == strType)
    {
        *num = NAN;
        if (outStrType)
        {
            *outStrType = numstr_StrType_Invalid;
        }
        return off;
    }
    switch (strType)
    {
    case numstr_StrType_BIN:
    {
        char* end;
        *num = strtol(str + 2, &end, 2);
        break;
    }
    case numstr_StrType_OCT:
    {
        char* end;
        if (('o' == str[1]) || ('O' == str[1]))
        {
            *num = strtol(str + 2, &end, 8);
        }
        else
        {
            *num = strtol(str + 1, &end, 8);
        }
        break;
    }
    case numstr_StrType_DEC:
    {
        char* end;
        *num = strtol(str, &end, 10);
        break;
    }
    case numstr_StrType_HEX:
    {
        char* end;
        *num = strtol(str + 2, &end, 16);
        break;
    }
    case numstr_StrType_Float:
    {
        char* end;
        *num = strtod(str, &end);
        break;
    }
    default:
        assert(false);
        break;
    }
    *outStrType = strType;
    return off;
}






u32 numstr_num2str(char* buf, u32 bufSize, double x)
{
    double d = x - (double)(int)x;
    if (d < FLT_EPSILON)
    {
        return snprintf(buf, bufSize, "%.0f", x);
    }
    else
    {
        int i = (int)round(d * 1000000);
        if (0 == i % 100000)
        {
            return snprintf(buf, bufSize, "%.1f", x);
        }
        else if (0 == i % 10000)
        {
            return snprintf(buf, bufSize, "%.2f", x);
        }
        else if (0 == i % 1000)
        {
            return snprintf(buf, bufSize, "%.3f", x);
        }
        else if (0 == i % 100)
        {
            return snprintf(buf, bufSize, "%.4f", x);
        }
        else if (0 == i % 10)
        {
            return snprintf(buf, bufSize, "%.5f", x);
        }
        else
        {
            return snprintf(buf, bufSize, "%f", x);
        }
    }
}






















































































