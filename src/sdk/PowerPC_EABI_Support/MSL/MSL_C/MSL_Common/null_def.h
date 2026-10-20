#ifndef _MSL_NULL_DEF_H
#define _MSL_NULL_DEF_H

#ifdef __cplusplus

#define NULL 0
#define nullptr NULL

#else
#ifndef NULL
#define NULL (void *)0
#endif
#endif

#endif
