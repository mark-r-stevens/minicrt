#include "libctiny.h"
#include <windows.h>

__declspec(noreturn) void __cdecl _invalid_parameter_noinfo_noreturn()
{
    ExitProcess(100);
}

extern "C" int __cdecl _purecall()
{
    ExitProcess(101);
}

namespace std
{
    __declspec(noreturn) void __cdecl _Xbad_function_call()
    {
        ExitProcess(102);
    }
}
