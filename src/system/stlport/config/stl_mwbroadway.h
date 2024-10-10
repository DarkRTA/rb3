// Custom configuration header for MWCC and the decomp project

#define _STLP_NATIVE_INCLUDE_PATH              sdk/PowerPC_EABI_Support/MSL/MSL_C++
#define _STLP_NATIVE_C_INCLUDE_PATH            sdk/PowerPC_EABI_Support/MSL/MSL_C

#include "compiler_macros.h"

#if __option(longlong) || defined(DECOMP_IDE_FLAG)
# define _STLP_LONG_LONG  long long
#endif

#if !__option(wchar_type) || defined(DECOMP_IDE_FLAG)
# define _STLP_WCHAR_T_IS_USHORT
#endif

#define _STLP_BIG_ENDIAN

#define _STLP_CMATH_ONLY_VENDOR

#undef _STLP_NO_UNCAUGHT_EXCEPT_SUPPORT
#undef _STLP_NO_UNEXPECTED_EXCEPT_SUPPORT

// Hack to fix various incorrect preprocessor paths in VS Code
// due to our C/C++ configuration settings
#ifdef __VS_CODE__
#undef __linux__
#endif

// Not used in STLport 5.0.3, preserved for posterity
// #include <sdk/PowerPC_EABI_Support/MSL/MSL_C++/msl_utility>
// #define _STLP_HAS_TRIVIAL_CONSTRUCTOR(T) Metrowerks::has_trivial_default_ctor<T>::value
// #define _STLP_HAS_TRIVIAL_COPY(T) Metrowerks::has_trivial_copy_ctor<T>::value
// #define _STLP_HAS_TRIVIAL_ASSIGN(T) Metrowerks::has_trivial_assignment<T>::value
// #define _STLP_HAS_TRIVIAL_DESTRUCTOR(T) Metrowerks::has_trivial_dtor<T>::value
// #define _STLP_IS_POD(T) Metrowerks::is_POD<T>::value
// #define _STLP_HAS_TYPE_TRAITS_INTRINSICS
