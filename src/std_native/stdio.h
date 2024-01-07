#ifndef _STDIO_H
#define _STDIO_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "PowerPC_EABI_Support/MSL_C/MSL_Common/stdio_api.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/FILE_POS.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/file_io.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/printf.h"
#include "PowerPC_EABI_Support/MSL_C/MSL_Common/scanf.h"

// Unorganized things which have yet to be RE'd

// TODO
// #define EOF
// #define FOPEN_MAX
// #define FILENAME_MAX
// #define BUFSIZ
// #define TMP_MAX
// #define L_tmpnam

int getc(FILE *stream);
char *gets(char *str);
int ungetc(int ch, FILE *stream);
int putc(int ch, FILE *stream);
int puts(const char *str);
int getchar(void);
int putchar(int ch);

void setbuf(FILE *restrict stream, char *restrict buffer);
int setvbuf(FILE *restrict stream, char *restrict buffer, int mode, size_t size);

int fgetc(FILE *stream);
int fputc(int ch, FILE *stream);
char *fgets(char *restrict str, int count, FILE *restrict stream);
int fputs(const char *restrict str, FILE *restrict stream);

void clearerr(FILE *stream);
int feof(FILE *stream);
int ferror(FILE *stream);
void perror(const char *s);

int remove(const char *pathname);
int rename(const char *old_filename, const char *new_filename);
FILE *tmpfile(void);
char *tmpnam(char *filename);

#ifdef __cplusplus
}
#endif

#endif
