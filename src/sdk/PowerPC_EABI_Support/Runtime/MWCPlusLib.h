#ifndef _RUNTIME_MWCPLUSLIB_H
#define _RUNTIME_MWCPLUSLIB_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void *ConstructorDestructor;

extern void __construct_array(void *ptr, ConstructorDestructor ctor, ConstructorDestructor dtor, size_t size, size_t n);
extern void __destroy_arr(void *block, ConstructorDestructor *dtor, size_t size, size_t n);

extern void *__construct_new_array(void *block, ConstructorDestructor ctor, ConstructorDestructor dtor_arg, size_t size, size_t n);
extern void __destroy_new_array(void *block, ConstructorDestructor dtor);
extern void __destroy_new_array2();
extern void __destroy_new_array3();

#ifdef __cplusplus
}
#endif

#endif
