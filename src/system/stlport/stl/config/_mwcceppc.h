// STLport configuration file
// It is internal STLport header - DO NOT include it directly

#define _STLP_COMPILER "Metrowerks CodeWarrior"

// Not available
// // Bring in definition of __MSL__ and related items
// #include <mslGlobals.h>
// #include <ansi_parms.h>

#define _STLP_STATIC_ASSERT(expr) __static_assert(expr, #expr);

#define _STLP_USE_UNIX_EMULATION_IO  1

#ifdef __INTEL__
#  define _STLP_LITTLE_ENDIAN
#else
#  define _STLP_BIG_ENDIAN
#endif

#if defined(_MSL_NO_LOCALE)
#  define _STLP_NO_IMPORT_LOCALE
#endif

// No -l or -f prefix versions of math.h functions
#define _STLP_NO_VENDOR_MATH_L 1
#define _STLP_NO_VENDOR_MATH_F 1

// Manual include paths
#define _STLP_NATIVE_INCLUDE_PATH              sdk/PowerPC_EABI_Support/MSL/MSL_C++
#define _STLP_NATIVE_C_INCLUDE_PATH            sdk/PowerPC_EABI_Support/MSL/MSL_C
#define _STLP_NATIVE_CPP_C_INCLUDE_PATH        sdk/PowerPC_EABI_Support/MSL/MSL_C++
#define _STLP_NATIVE_CPP_RUNTIME_INCLUDE_PATH  sdk/PowerPC_EABI_Support/MSL/MSL_C++
