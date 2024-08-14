#ifndef COMPILER_MACROS_H
#define COMPILER_MACROS_H

#ifndef __MWERKS__
#define __option(x)
#define __declspec(x)
#define __attribute__(x)
#endif

#define ALIGN(x) __attribute__((aligned(x)))

// There are two attributes for this for whatever reason
// The __attribute__ didn't work on ec::malloc(), the __declspec errors on class methods
// Just try both and see which works lol
#define DONT_INLINE __declspec(noinline) // use for regular functions
#define DONT_INLINE_CLASS __attribute__((never_inline)) // use for class methods

#define DECL_SECTION(x) __declspec(section x)
#define DECL_WEAK __declspec(weak)

#endif
