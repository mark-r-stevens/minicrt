#include "libctiny.h"
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

// Force the linker to include USER32.LIB
#pragma comment(linker, "/defaultlib:user32.lib")

extern "C" int __cdecl vsprintf(char* buffer, const char* format, va_list vlist)
{
    return wvsprintfA(buffer, format, vlist);
}
