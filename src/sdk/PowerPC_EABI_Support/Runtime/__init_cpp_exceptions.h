#ifndef RUNTIME_INIT_CPP_EXCEPTIONS_H
#define RUNTIME_INIT_CPP_EXCEPTIONS_H

/* https://github.com/SwareJonge/mkdd/blob/main/libs/PowerPC_EABI_Support/include/PowerPC_EABI_Support/Runtime/__init_cpp_exceptions.h */

#ifdef __cplusplus
extern "C" {
#endif

void __init_cpp_exceptions(void);
void __fini_cpp_exceptions(void);

#ifdef __cplusplus
}
#endif

#endif
