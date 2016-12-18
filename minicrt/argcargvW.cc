//==========================================
// LIBCTINY - Matt Pietrek 2001
// MSDN Magazine, January 2001
//==========================================
#include "libctiny.h"
#include <windows.h>
#include "argcargv.h"

#define _MAX_CMD_LINE_ARGS  128

wchar_t * _ppszArgvW[_MAX_CMD_LINE_ARGS+1];

int __cdecl _ConvertCommandLineToArgcArgvW() {
    int cbCmdLine;
    int argc;
    PWSTR pszSysCmdLine, pszCmdLine;
    
    // Set to no argv elements, in case we have to bail out
    _ppszArgvW[0] = 0;

    // First get a pointer to the system's version of the command line, and
    // figure out how long it is.
    pszSysCmdLine = GetCommandLineW();
    cbCmdLine = lstrlenW( pszSysCmdLine );

    // Allocate memory to store a copy of the command line.  We'll modify
    // this copy, rather than the original command line.  Yes, this memory
    // currently doesn't explicitly get freed, but it goes away when the
    // process terminates.
    pszCmdLine = (PWSTR)HeapAlloc( GetProcessHeap(), 0, sizeof(wchar_t)*(cbCmdLine+1) );
    if (!pszCmdLine)
        return 0;

    // Copy the system version of the command line into our copy
    lstrcpynW( pszCmdLine, pszSysCmdLine , cbCmdLine+1);

    if ('"' == *pszCmdLine)   // If command line starts with a quote ("),
    {                           // it's a quoted filename.  Skip to next quote.
        pszCmdLine++;
    
        _ppszArgvW[0] = pszCmdLine;  // argv[0] == executable name
    
        while (*pszCmdLine && (*pszCmdLine != '"'))
            pszCmdLine++;

        if (*pszCmdLine)      // Did we see a non-NULL ending?
            *pszCmdLine++ = 0;  // Null terminate and advance to next char
        else
            return 0;           // Oops!  We didn't see the end quote
    }
    else    // A regular (non-quoted) filename
    {
        _ppszArgvW[0] = pszCmdLine;  // argv[0] == executable name

        while (*pszCmdLine && (' ' != *pszCmdLine) && ('\t' != *pszCmdLine))
            pszCmdLine++;

        if (*pszCmdLine)
            *pszCmdLine++ = 0;  // Null terminate and advance to next char
    }

    // Done processing argv[0] (i.e., the executable name).  Now do th
    // actual arguments

    argc = 1;

    while (1)
    {
        // Skip over any whitespace
        while (*pszCmdLine && (' ' == *pszCmdLine) || ('\t' == *pszCmdLine))
            pszCmdLine++;

        if (0 == *pszCmdLine) // End of command line???
            return argc;

        if ('"' == *pszCmdLine)   // Argument starting with a quote???
        {
            pszCmdLine++;   // Advance past quote character

            _ppszArgvW[ argc++ ] = pszCmdLine;
            _ppszArgvW[ argc ] = 0;

            // Scan to end quote, or NULL terminator
            while (*pszCmdLine && (*pszCmdLine != '"'))
                pszCmdLine++;
                
            if (0 == *pszCmdLine)
                return argc;
            
            if (*pszCmdLine)
                *pszCmdLine++ = 0;  // Null terminate and advance to next char
        }
        else                        // Non-quoted argument
        {
            _ppszArgvW[ argc++ ] = pszCmdLine;
            _ppszArgvW[ argc ] = 0;

            // Skip till whitespace or NULL terminator
            while (*pszCmdLine && (' '!=*pszCmdLine) && ('\t'!=*pszCmdLine))
                pszCmdLine++;
            
            if (0 == *pszCmdLine)
                return argc;
            
            if (*pszCmdLine)
                *pszCmdLine++ = 0;  // Null terminate and advance to next char
        }

        if (argc >= (_MAX_CMD_LINE_ARGS))
            return argc;
    }
}
