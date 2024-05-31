#ifndef DECOMP_H
#define DECOMP_H

/**
 * https://github.com/kiwi515/ogws/blob/master/include/decomp.h
 * Codewarrior tricks for matching decomp
 * (Macros generate prototypes to satisfy -requireprotos)
 */

#define __CONCAT(x, y) x##y
#define CONCAT(x, y) __CONCAT(x, y)

// Compile without matching hacks.
#ifdef NON_MATCHING
#define DECOMP_FORCEACTIVE(module, ...)
#define DECOMP_FORCELITERAL(module, ...)
#define DECOMP_FORCEFUNC(module, decl, ...)
#define DECOMP_FORCEDTOR(module, cls)
#define DECOMP_FORCEBLOCK(module, ...)
// Compile with matching hacks.
// (This version of CW does not support pragmas inside macros.)
#else
// Force reference specific data
#define DECOMP_FORCEACTIVE(module, ...)                                        \
    void fake_function(...);                                                   \
    void CONCAT(FORCEACTIVE##module, __LINE__)(void);                          \
    void CONCAT(FORCEACTIVE##module, __LINE__)(void) {                         \
        fake_function(__VA_ARGS__);                                            \
    }

// Force literal ordering, such as floats in sdata2
#define DECOMP_FORCELITERAL(module, ...)                                       \
    void CONCAT(FORCELITERAL##module, __LINE__)(void);                         \
    void CONCAT(FORCELITERAL##module, __LINE__)(void) {                        \
        (__VA_ARGS__);                                                         \
    }

// Force referenced functions
#define DECOMP_FORCEFUNC(module, cls, func)                                    \
    void CONCAT(FORCEFUNC##module, __LINE__) (cls* dummy);                     \
    void CONCAT(FORCEFUNC##module, __LINE__) (cls* dummy) {                    \
        dummy->func;                                                           \
    }

// Force referenced destructor
#define DECOMP_FORCEDTOR(module, cls) DECOMP_FORCEFUNC(module, cls, ~cls())

// For more complex forcing requirements
// Example usage: DECOMP_FORCEBLOCK(Module, (Class* dummy, int arg),
//     dummy->Method(arg);
// )
#define DECOMP_FORCEBLOCK(module, params, ...)                                 \
    void CONCAT(FORCEBLOCK##module, __LINE__) params;                          \
    void CONCAT(FORCEBLOCK##module, __LINE__) params {                         \
        __VA_ARGS__                                                            \
    }
#endif

/*
 * ASM macros, to prevent IDEs from complaining
 */
#if defined(__MWERKS__)
#define ASM_DECL asm
#define ASM_BLOCK asm
#else
#define ASM_DECL
#define ASM_BLOCK(...)
#define __option(x)
#define __declspec(x)
#define __attribute__(x)
#endif


#endif
