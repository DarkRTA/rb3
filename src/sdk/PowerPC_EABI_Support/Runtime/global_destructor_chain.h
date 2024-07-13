#ifndef _GLOBALDESTRUCTORCHAIN
#define _GLOBALDESTRUCTORCHAIN

/* https://github.com/SwareJonge/mkdd/blob/main/libs/PowerPC_EABI_Support/include/PowerPC_EABI_Support/Runtime/global_destructor_chain.h */

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CTORARG_TYPE int
#define CTORARG_COMPLETE (1)
#define CTORARG_PARTIAL (0)

#define CTORCALL_COMPLETE(ctor, objptr) (((void (*)(void *, CTORARG_TYPE))ctor)(objptr, CTORARG_COMPLETE))
#define CTORCALL_PARTIAL(ctor, objptr) (((void (*)(void *, CTORARG_TYPE))ctor)(objptr, CTORARG_PARTIAL))

#define DTORARG_TYPE int
#define DTORARG_COMPLETE (-1)
#define DTORARG_PARTIAL (0)

#define DTORCALL_COMPLETE(dtor, objptr) (((void (*)(void *, DTORARG_TYPE))dtor)(objptr, DTORARG_COMPLETE))
#define DTORCALL_PARTIAL(dtor, objptr) (((void (*)(void *, DTORARG_TYPE))dtor)(objptr, DTORARG_PARTIAL))

typedef struct DestructorChain {
    struct DestructorChain *next;
    void *destructor;
    void *object;
} DestructorChain;

void *__register_global_object(void *object, void *destructor, DestructorChain *regmem);
void __destroy_global_chain(void);
int __register_atexit(void (*)(void));

#ifdef __cplusplus
}
#endif

#endif
