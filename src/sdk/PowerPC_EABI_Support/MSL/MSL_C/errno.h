#ifndef _ERRNO_H
#define _ERRNO_H

#include "compiler_macros.h"

#ifdef __cplusplus
extern "C" {
#endif

/* clang-format off */
/* Leave numbers aligned */
#define ENOERR        0
#define EPERM         1
#define ENOENT        2
#define ESRCH         3
#define EINTR         4
#define EIO           5
#define ENXIO         6
#define E2BIG         7
#define ENOEXEC       8
#define EBADF         9
#define ECHILD        10
#define EAGAIN        11
#define ENOMEM        12
#define EACCES        13
#define EFAULT        14
#define EBUSY         16
#define EEXIST        17
#define EXDEV         18
#define ENODEV        19
#define ENOTDIR       20
#define EISDIR        21
#define EINVAL        22
#define ENFILE        23
#define EMFILE        24
#define ENOTTY        25
#define ESIGPARM      26
#define EFBIG         27
#define ENOSPC        28
#define ESPIPE        29
#define EROFS         30
#define EMLINK        31
#define EPIPE         32
#define EDOM          33
#define ERANGE        34
#define EDEADLK       35
#define EDEADLOCK     EDEADLK
#define ENAMETOOLONG  36
#define ENOSYS        38
#define ENOTEMPTY     39
#define EFPOS         40

#define ENOLCK        77
#define EILSEQ        88
#define EUNKNOWN      99
/* clang-format on */

DECL_SECTION(".sdata") extern int errno;

#ifdef __cplusplus
}
#endif

#endif
