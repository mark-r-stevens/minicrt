#include "libctiny.h"
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>

// Force the linker to include USER32.LIB
#pragma comment(linker, "/defaultlib:user32.lib")

// NOTE: maxlen is ignored
extern "C" int __cdecl swprintf (wchar_t *string, size_t maxlen, const wchar_t *format, ...)
{
    int retValue;
    va_list argptr;

    va_start( argptr, format );
    retValue = wvsprintfW( string, format, argptr );
    va_end( argptr );

    return retValue;
}

