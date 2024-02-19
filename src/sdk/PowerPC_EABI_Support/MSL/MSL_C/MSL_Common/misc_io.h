#ifndef _MSL_MISC_IO_H
#define _MSL_MISC_IO_H

#ifdef __cplusplus
extern "C" {
#endif

void (*__stdio_exit)(void);

void __stdio_atexit();

#ifdef __cplusplus
}
#endif

#endif
