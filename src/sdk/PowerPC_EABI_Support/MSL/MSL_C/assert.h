#ifndef _ASSERT_H
#define _ASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "MSL_Common/assert_api.h"

#ifdef NDEBUG
#define assert(condition) ((void)0)
#else
#define assert(condition) ((condition) ? ((void)0) : __msl_assertion_failed(#condition, __FILE__, 0, __LINE__))
#endif

#ifdef __cplusplus
}
#endif

#endif
