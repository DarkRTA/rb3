/* https://github.com/SwareJonge/mkdd/blob/main/libs/PowerPC_EABI_Support/src/Runtime/__init_cpp_exceptions.cpp */

#include "__init_cpp_exceptions.h"

#include "decomp.h"
#include "MWCPlusLib.h"
#include "NMWException.h"
#include "__ppc_eabi_linker.h"

static int fragmentID = -2;

void __init_cpp_exceptions() {
    if (fragmentID == -2) {
        register char *R2;
        ASM_BLOCK(mr R2, r2)
        fragmentID = __register_fragment(_eti_init_info, R2);
    }
}

void __fini_cpp_exceptions() {
    if (fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

DECL_SECTION(".ctors") extern void *const __init_cpp_exceptions_reference = __init_cpp_exceptions;
DECL_SECTION(".dtors") extern void *const __destroy_global_chain_reference = __destroy_global_chain;
DECL_SECTION(".dtors") extern void *const __fini_cpp_exceptions_reference = __fini_cpp_exceptions;
