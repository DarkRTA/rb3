#ifndef COMPILER_MACROS_H
#define COMPILER_MACROS_H

#ifndef __MWERKS__
#define __option(x)
#define __declspec(x)
#define __attribute__(x)
#endif

#define ALIGN(x) __attribute__((aligned(x)))
#define DONT_INLINE __declspec(noinline)

#define DECL_SECTION(x) __declspec(section x)
#define DECL_WEAK __declspec(weak)

#endif
