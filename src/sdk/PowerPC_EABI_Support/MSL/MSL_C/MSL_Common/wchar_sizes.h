#ifndef _MSL_WCHAR_SIZES_H
#define _MSL_WCHAR_SIZES_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef WCHAR_MIN
#define WCHAR_MIN 0x0000
#endif

#ifndef WCHAR_MAX
#define WCHAR_MAX 0xffff
#endif

#ifndef WINT_MIN
#define WINT_MIN WCHAR_MIN
#endif

#ifndef WINT_MAX
#define WINT_MAX WCHAR_MAX
#endif

#ifdef __cplusplus
}
#endif

#endif
