#ifndef _SETJMP_H
#define _SETJMP_H

#include "PowerPC_EABI_Support/Runtime/Gecko_setjmp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __jmp_buf jmp_buf;
#define setjmp(env) __setjmp(&env)

#ifdef __cplusplus
}
#endif

#endif
