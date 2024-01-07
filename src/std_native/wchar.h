#ifndef _WCHAR_H
#define _WCHAR_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/wchar_io.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/wcstoul.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/wmem.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/wprintf.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/wscanf.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/wstring.h"

#define WCHAR_MIN 0x0000
#define WCHAR_MAX 0xffff

// #define WEOF

size_t wcsftime(wchar_t *str, size_t count, const wchar_t *format, tm *time);

#ifdef __cplusplus
}
#endif

#endif
