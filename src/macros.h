#ifndef MACROS_H
#define MACROS_H

// Possibilities for the GAME_VERSION define
// Be sure to update if the list in configure.py changes!
#define VERSION_SZBE69 0
#define VERSION_SZBE69_BE 1

// Useful macros
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define CLAMP(low, high, x) ((x) > (high) ? (high) : ((x) < (low) ? (low) : (x)))

#define ROUND_UP(x, align) (((x) + (align)-1) & (-(align)))
#define ROUND_UP_PTR(x, align) ((void *)((((u32)(x)) + (align)-1) & (~((align)-1))))

#define ROUND_DOWN(x, align) ((x) & (-(align)))
#define ROUND_DOWN_PTR(x, align) ((void *)(((u32)(x)) & (~((align)-1))))

#define ROTATE_LEFT(x, i)  (((x) << (i)) | ((x) >> ((sizeof((x)) * 8) - (i))))
#define ROTATE_RIGHT(x, i) (((x) >> (i)) | ((x) << ((sizeof((x)) * 8) - (i))))

#define ARRAY_LENGTH(x) (sizeof((x)) / sizeof((x)[0]))

// Codewarrior tricks for matching decomp
// (Functions are given prototypes for -requireprotos)
#ifdef __MWERKS__
// Force BSS order
#define CW_FORCE_BSS(module, ...)                                                        \
    void fake_function(...);                                                             \
    void FORCE_BSS##module##x(void);                                                     \
    void FORCE_BSS##module##x(void) {                                                    \
        fake_function(__VA_ARGS__);                                                      \
    }
// Force strings into pool
#define CW_FORCE_STRINGS(module, ...)                                                    \
    void fake_function(...);                                                             \
    void FORCE_STRINGS##module(void);                                                    \
    void FORCE_STRINGS##module(void) {                                                   \
        fake_function(__VA_ARGS__);                                                      \
    }
#else
#define CW_FORCE_BSS(module, ...)
#define CW_FORCE_STRINGS(module, ...)
#endif

// For VSCode
#ifdef __MWERKS__
#define ASM_DECL asm
#define ASM_BLOCK asm
#else
#define ASM_DECL
#define ASM_BLOCK(...)
#define __option(x)
#define __declspec(x)
#define __attribute__(x)
#endif

#define ALIGN(x) __attribute__((aligned(x)))
#define DONT_INLINE __attribute__((never_inline))

#define DECL_SECTION(x) __declspec(section x)
#define DECL_WEAK __declspec(weak)

#endif
