//
// corecrt_stdio_config.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Per-module <stdio.h> configuration.
//
#pragma once

#include <corecrt.h>

_CRT_BEGIN_C_HEADER

#if !defined _NO_CRT_STDIO_INLINE && !_CRT_FUNCTIONS_REQUIRED
    #define _NO_CRT_STDIO_INLINE
#endif

#if defined _NO_CRT_STDIO_INLINE
    #undef _CRT_STDIO_INLINE
    #define _CRT_STDIO_INLINE _CRTIMP
#elif !defined _CRT_STDIO_INLINE
    #define _CRT_STDIO_INLINE __inline
#endif

#if defined _ATL_XP_TARGETING
#define _CRT_STDIO_INLINE_VISTA_OR_LATER _CRTIMP
#define _CRT_STDIO_INLINE_AWAYS_FOR_XP   __inline
#else
#define _CRT_STDIO_INLINE_VISTA_OR_LATER _CRT_STDIO_INLINE
#define _CRT_STDIO_INLINE_AWAYS_FOR_XP   _CRT_STDIO_INLINE
#endif

#define _CRT_STDIO_INLINE_AWAYS          __inline

#if !defined RC_INVOKED // RC has no target architecture
    #if defined _M_IX86
        #define _CRT_INTERNAL_STDIO_SYMBOL_PREFIX "_"
    #elif defined _M_X64 || defined _M_ARM || defined _M_ARM64
        #define _CRT_INTERNAL_STDIO_SYMBOL_PREFIX ""
    #else
        #error Unsupported architecture
    #endif
#endif



// Predefine _CRT_STDIO_ISO_WIDE_SPECIFIERS to use ISO-conforming behavior for
// the wide string printf and scanf functions (%s, %c, and %[] specifiers).
//
// Predefine _CRT_STDIO_LEGACY_WIDE_SPECIFIERS to use VC++ 2013 and earlier behavior for
// the wide string printf and scanf functions (%s, %c, and %[] specifiers).
//
// Predefine _CRT_STDIO_ARBITRARY_WIDE_SPECIFIERS when building code that does
// not use these format specifiers without a length modifier and thus can be
// used with either the legacy (default) or the conforming mode.  (This option
// is intended for use by static libraries).
#if !defined RC_INVOKED // _CRT_STDIO_LEGACY_WIDE_SPECIFIERS et al. are too long for rc
    #if defined _CRT_STDIO_ISO_WIDE_SPECIFIERS
        #if defined _CRT_STDIO_LEGACY_WIDE_SPECIFIERS
            #error _CRT_STDIO_ISO_WIDE_SPECIFIERS and _CRT_STDIO_LEGACY_WIDE_SPECIFIERS cannot be defined together.
        #endif

        #if !defined _M_CEE_PURE
            #pragma comment(lib, "iso_stdio_wide_specifiers")
            #pragma comment(linker, "/include:" _CRT_INTERNAL_STDIO_SYMBOL_PREFIX "__PLEASE_LINK_WITH_iso_stdio_wide_specifiers.lib")
        #endif
    #elif defined _CRT_STDIO_LEGACY_WIDE_SPECIFIERS
        #if !defined _M_CEE_PURE
            #pragma comment(lib, "legacy_stdio_wide_specifiers")
            #pragma comment(linker, "/include:" _CRT_INTERNAL_STDIO_SYMBOL_PREFIX "__PLEASE_LINK_WITH_legacy_stdio_wide_specifiers.lib")
        #endif
    #endif

    #if defined __cplusplus && !defined _CRT_STDIO_ARBITRARY_WIDE_SPECIFIERS
        #ifdef _CRT_STDIO_ISO_WIDE_SPECIFIERS
            #pragma detect_mismatch("_CRT_STDIO_ISO_WIDE_SPECIFIERS", "1")
        #else
            #pragma detect_mismatch("_CRT_STDIO_ISO_WIDE_SPECIFIERS", "0")
        #endif
    #endif
#endif

// If we're compiling mixed managed code, make sure these inline functions are
// compiled as native to ensure that there is only one instance of each of the
// function-local static variables.
#if defined _M_CEE && !defined _M_CEE_PURE
    #pragma managed(push, off)
#endif

#if _CRT_FUNCTIONS_REQUIRED
    // This function must not be inlined into callers to avoid ODR violations.  The
    // static local variable has different names in C and in C++ translation units.
    _Check_return_ _Ret_notnull_
    __declspec(noinline) __inline unsigned __int64* __CRTDECL __local_stdio_printf_options(void)
    {
        static unsigned __int64 _OptionsStorage;
        return &_OptionsStorage;
    }

    // This function must not be inlined into callers to avoid ODR violations.  The
    // static local variable has different names in C and in C++ translation units.
    _Check_return_ _Ret_notnull_
    __declspec(noinline) __inline unsigned __int64* __CRTDECL __local_stdio_scanf_options(void)
    {
        static unsigned __int64 _OptionsStorage;
        return &_OptionsStorage;
    }
#endif

#if defined _M_CEE && !defined _M_CEE_PURE
    #pragma managed(pop)
#endif

#define _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS (*__local_stdio_printf_options())
#define _CRT_INTERNAL_LOCAL_SCANF_OPTIONS  (*__local_stdio_scanf_options ())



#define _CRT_INTERNAL_PRINTF_LEGACY_VSPRINTF_NULL_TERMINATION (1ULL << 0)
#define _CRT_INTERNAL_PRINTF_STANDARD_SNPRINTF_BEHAVIOR       (1ULL << 1)
#define _CRT_INTERNAL_PRINTF_LEGACY_WIDE_SPECIFIERS           (1ULL << 2)
#define _CRT_INTERNAL_PRINTF_LEGACY_MSVCRT_COMPATIBILITY      (1ULL << 3)
#define _CRT_INTERNAL_PRINTF_LEGACY_THREE_DIGIT_EXPONENTS     (1ULL << 4)


#define _CRT_INTERNAL_SCANF_SECURECRT                   (1ULL << 0)
#define _CRT_INTERNAL_SCANF_LEGACY_WIDE_SPECIFIERS      (1ULL << 1)
#define _CRT_INTERNAL_SCANF_LEGACY_MSVCRT_COMPATIBILITY (1ULL << 2)



_CRT_END_C_HEADER
