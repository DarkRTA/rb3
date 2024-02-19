#ifndef _MSL_CONSOLE_IO_H
#define _MSL_CONSOLE_IO_H

#include "file_def.h"

#ifdef __cplusplus
extern "C" {
#endif

int __read_console(__file_handle handle, unsigned char* buffer, size_t* count, __ref_con ref_con);
int __write_console(__file_handle handle, unsigned char* buffer, size_t* count, __ref_con ref_con);
int __close_console(__file_handle handle);

#ifdef __cplusplus
}
#endif

#endif
