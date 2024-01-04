// STLport configuration file
// It is internal STLport header - DO NOT include it directly

#define _STLP_COMPILER "Metrowerks CodeWarrior"

// Not available
// // Bring in definition of __MSL__ and related items
// #include <mslGlobals.h>
// #include <ansi_parms.h>

#if __option(longlong)
#  define _STLP_LONG_LONG  long long
#endif

#define _STLP_USE_UNIX_EMULATION_IO  1

#define _STLP_USE_AUTO_PTR_CONVERSIONS  1

#ifdef __INTEL__
#  define _STLP_LITTLE_ENDIAN
#else
#  define _STLP_BIG_ENDIAN
#endif

#if defined(_MSL_NO_LOCALE)
#  define _STLP_NO_IMPORT_LOCALE
#endif

#if !__option( wchar_type )
#  define _STLP_WCHAR_T_IS_USHORT
#endif

//  *** Version-specific settings ***

#if __MWERKS__ >= 0x2405
#  define _STLP_HAS_NATIVE_FLOAT_ABS
#endif

// Remaining version checks omitted since they aren't relevant to this project
// (__MWERKS__ == 0x4301)

// Manual include path
# define _STLP_NATIVE_INCLUDE_PATH std
