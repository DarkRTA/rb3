#ifndef STDIO_API_H
#define STDIO_API_H

#include "types.h"
#include "sdk/MSL_C/MSL_Common/file_struc.h"
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

enum __ReadProcActions {
	__GetAChar,
	__UngetAChar,
	__TestForError
};

enum __WReadProcActions
{
	__GetAwChar,
	__UngetAwChar,
	__TestForwcsError
};

typedef struct {
	char* CharStr;
	size_t MaxCharCount;
	size_t CharsWritten;
} __OutStrCtrl;

typedef struct{
	char* NextChar;
	int NullCharDetected;
} __InStrCtrl;

typedef struct {
	wchar_t * wCharStr;
	size_t MaxCharCount;
	size_t CharsWritten;
} __wOutStrCtrl;

typedef struct {
	wchar_t * wNextChar;
	int    wNullCharDetected;
} __wInStrCtrl;

//__fread
size_t __fwrite(const void *pPtr, size_t memb_size, size_t num_memb, FILE *file);
int __StringRead(void *, int, int);
wint_t __wStringRead(void*, wint_t, int);

#ifdef __cplusplus
}
#endif

#endif // STDIO_API_H
