#ifndef _MSL_RESTRICT_DEF_H
#define _MSL_RESTRICT_DEF_H

#if !defined(__cplusplus) && __STDC_VERSION__ >= 199901L
#define RESTRICT restrict
#else
#define RESTRICT
#endif

#endif
