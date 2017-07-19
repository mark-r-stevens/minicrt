#include "libctiny.h"
#include <windows.h>

extern "C" {

#ifdef _WIN64
#define kDefaultSecurityCookie 0x2B992DDFA23249D6
#else  /* _WIN64 */
#define kDefaultSecurityCookie 0xBB40E64E
#endif  /* _WIN64 */

#if _MSC_VER >= 1900
typedef uintptr_t cookie_type;
#else
typedef DWORD_PTR cookie_type;
#endif

cookie_type __security_cookie = kDefaultSecurityCookie;

void __fastcall __security_check_cookie(cookie_type) {
    return;

    /* Immediately return if the local cookie is OK. */
    // if (cookie == __security_cookie)
    //    return;

    /* Report the failure */
    // report_failure();
}

};  // extern "C"
