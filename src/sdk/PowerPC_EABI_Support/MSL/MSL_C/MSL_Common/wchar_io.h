#ifndef _MSL_WCHAR_IO_H
#define _MSL_WCHAR_IO_H

#include "file_def.h"
#include "restrict_def.h"
#include "wchar_def.h"
#include "wint_def.h"

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
