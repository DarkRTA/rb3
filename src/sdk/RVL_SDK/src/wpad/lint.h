#ifndef RVL_SDK_WPAD_INTERNAL_LINT_H
#define RVL_SDK_WPAD_INTERNAL_LINT_H

/* no public header */

/*******************************************************************************
 * macros
 */

#define LINTNextElement(a, b)	((&((a)[b]))[1])

/*******************************************************************************
 * types
 */

#ifdef __cplusplus
	extern "C" {
#endif

typedef unsigned long ULONG;

/*******************************************************************************
 * functions
 */

int LINTCmp(const ULONG *lhs, const ULONG *rhs);
void LINTLshift(ULONG *dst, ULONG *src, ULONG shift);
int LINTMsb(const ULONG *data);
void LINTSub(ULONG *dst, const ULONG *lhs, const ULONG *rhs);
void LINTMul(ULONG *dst, const ULONG *lhs, const ULONG *rhs);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_WPAD_INTERNAL_LINT_H
