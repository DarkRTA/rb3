/* https://github.com/SwareJonge/mkdd/blob/main/libs/PowerPC_EABI_Support/src/Runtime/global_destructor_chain.c
 */

#include "MWCPlusLib.h"

#ifdef __cplusplus
extern "C" {
#endif

DestructorChain *__global_destructor_chain;

void *__register_global_object(void *object, void *destructor, DestructorChain *regmem) {
    regmem->next = __global_destructor_chain;
    regmem->destructor = destructor;
    regmem->object = object;
    __global_destructor_chain = regmem;

    return object;
}

void __destroy_global_chain(void) {
    DestructorChain *iter;

    while ((iter = __global_destructor_chain) != 0) {
        __global_destructor_chain = iter->next;
        DTORCALL_COMPLETE(iter->destructor, iter->object);
    }
}

int __register_atexit(void (*func)(void)) {}

__declspec(section ".dtors") static void *const __destroy_global_chain_reference = __destroy_global_chain;

#ifdef __cplusplus
}
#endif
