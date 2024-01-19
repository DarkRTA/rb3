#ifndef _WCHAR_IO_H
#define _WCHAR_IO_H

#include <stdio.h>
#include "macros.h"
#include "sdk/MSL_C/MSL_Common/wchar_def.h"

#ifdef __cplusplus
extern "C" {
#endif

wint_t getwchar();
wint_t putwchar(wchar_t ch);
wint_t getwc(FILE *stream);
wint_t putwc(wchar_t ch, FILE *stream);
wint_t ungetwc(wint_t ch, FILE *stream);

int fwide(FILE *stream, int mode);

wint_t fgetwc(FILE *stream);
wint_t fputwc(wchar_t ch, FILE *stream);
wchar_t *fgetws(wchar_t *RESTRICT str, int count, FILE *RESTRICT stream);
int fputws(const wchar_t *RESTRICT str, FILE *RESTRICT stream);

#ifdef __cplusplus
}
#endif

#endif
