#include "libctiny.h"
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

// Force the linker to include USER32.LIB
#pragma comment(linker, "/defaultlib:user32.lib")

extern "C" int __cdecl vprintf(const char* format, va_list vlist)
{
    char buf[1024];
    int retValue;
    DWORD cbWritten;
    retValue = wvsprintfA(buf, format, vlist);
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), buf, retValue, &cbWritten, 0);
    return retValue;
}
