#ifndef _STDIO_H
#define _STDIO_H

#include "MSL_Common/stdio_api.h"
#include "MSL_Common/FILE_POS.h"
#include "MSL_Common/file_io.h"
#include "MSL_Common/printf.h"
#include "MSL_Common/scanf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Unorganized things which have yet to be RE'd */

#define EOF -1

/* TODO
#define FOPEN_MAX
#define FILENAME_MAX
#define BUFSIZ
#define TMP_MAX
#define L_tmpnam
*/

int getc(FILE *stream);
char *gets(char *str);
int ungetc(int ch, FILE *stream);
int putc(int ch, FILE *stream);
int puts(const char *str);
int getchar(void);
int putchar(int ch);

void setbuf(FILE *RESTRICT stream, char *RESTRICT buffer);
int setvbuf(FILE *RESTRICT stream, char *RESTRICT buffer, int mode, size_t size);

int fgetc(FILE *stream);
int fputc(int ch, FILE *stream);
char *fgets(char *RESTRICT str, int count, FILE *RESTRICT stream);
int fputs(const char *RESTRICT str, FILE *RESTRICT stream);

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
