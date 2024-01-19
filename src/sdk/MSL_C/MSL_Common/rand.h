#ifndef _MSL_RAND_H
#define _MSL_RAND_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// TODO
// #define RAND_MAX

int rand();
void srand(u32 seed);

#ifdef __cplusplus
}
#endif

#endif
