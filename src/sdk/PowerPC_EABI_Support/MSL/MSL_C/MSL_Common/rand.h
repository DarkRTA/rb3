#ifndef _MSL_RAND_H
#define _MSL_RAND_H

#ifdef __cplusplus
extern "C" {
#endif

/* TODO
#define RAND_MAX
*/

int rand();
void srand(unsigned int seed);

#ifdef __cplusplus
}
#endif

#endif
