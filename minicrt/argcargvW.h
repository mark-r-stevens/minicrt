#ifndef TR_COMMON_MINICRT_ARGCARGV_H_
#define TR_COMMON_MINICRT_ARGCARGV_H_

#include "libctiny.h"

extern wchar_t * _ppszArgvW[];

int __cdecl _ConvertCommandLineToArgcArgvW();

#endif  // TR_COMMON_MINICRT_ARGCARGV_H_
