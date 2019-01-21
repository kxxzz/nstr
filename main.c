#include <stdlib.h>
#ifdef _WIN32
# include <crtdbg.h>
#endif



#include <stdio.h>
#include <assert.h>
#include <float.h>
#include <math.h>
#include <string.h>

#include "nstr.h"




#ifdef ARYLEN
# undef ARYLEN
#endif
#define ARYLEN(a) (sizeof(a) / sizeof((a)[0]))



static bool float_eq(float a, float b)
{
    return fabs(a - b) <= FLT_EPSILON;
}
static bool float_eq_almost(float a, float b)
{
    return fabs(a - b) <= 0.00001;
}




static void test(void)
{
    double x;
    NSTR_StrType strType;
    u32 off;
    const char* s[NSTR_NumStrTypes] =
    {
        "0b101101",
        "055",
        "45",
        "0x2d",
        "45.",
    };
    for (u32 i = 0; i < ARYLEN(s); ++i)
    {
        off = NSTR_str2num(&x, s[i], (u32)strlen(s[i]), &strType);
        assert(i == strType);
        assert((u32)strlen(s[i]) == off);
        assert(float_eq(45, (float)x));
        char buf[255] = "";
        u32 off1 = NSTR_num2str(buf, sizeof(buf), x);
        assert(2 == off1);
        printf("%s\n", buf);
    }
}





static int mainReturn(int r)
{
#if !defined(NDEBUG) && defined(_WIN32)
    system("pause");
#endif
    return r;
}


int main(int argc, char* argv[])
{
    test();
    mainReturn(0);
}



















































































