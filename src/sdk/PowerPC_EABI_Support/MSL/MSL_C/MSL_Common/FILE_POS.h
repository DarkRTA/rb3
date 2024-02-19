#ifndef _MSL_FILE_POS_H
#define _MSL_FILE_POS_H

#include "file_def.h"
#include "restrict_def.h"

#ifdef __cplusplus
extern "C" {
#endif

int fseek(FILE *stream, unsigned int offset, int whence);
int _fseek(FILE *stream, unsigned int offset, int whence);
int ftell(FILE *stream);
int _ftell(FILE *stream);

int fgetpos(FILE *RESTRICT stream, fpos_t *RESTRICT pos);
int fsetpos(FILE *stream, const fpos_t *pos);
void rewind(FILE *stream);

#ifdef __cplusplus
}
#endif

#endif
