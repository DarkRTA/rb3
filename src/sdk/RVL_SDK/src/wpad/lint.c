#include "lint.h"
//#if 0

/*******************************************************************************
 * headers
 */

#include <limits.h>
#include <string.h> // memset
#include "types.h"

/*******************************************************************************
 * macros
 */

#define ULONG_BIT				(sizeof(ULONG) * CHAR_BIT)
#define ULLONG_BIT				(sizeof(u64) * CHAR_BIT)

#define ULLONG_ULONG_BIT_DIFF	(ULLONG_BIT - ULONG_BIT)

/*******************************************************************************
 * explanation
 *
 * so basically these LINT* functions operate on these buffers where
 *
 *	struct LINTBuf
 *	{
 *		ULONG	size;
 *		ULONG	data[size];
 *		ULONG	terminator = 0;
 *	};
 *
 * i also tried to make the functions here as type-generic as possible, but some
 * assumptions within the functions may inherently remain that there is a 32-bit
 * wide type and a 64-bit wide type on the machine
 *
 */

/*******************************************************************************
 * functions
 */

int LINTCmp(const u32 *lhs, const u32 *rhs)
{
	int i;

	u32 lhsSize = lhs[0];
	u32 rhsSize = rhs[0];

	const u32 *lhsData = lhs + 1;
	const u32 *rhsData = rhs + 1;

	if (lhsSize > rhsSize)
		return 1;

	if (lhsSize < rhsSize)
		return -1;

	for (i = lhsSize - 1; i >= 0; i--)
	{
		if (lhsData[i] > rhsData[i])
			return 1;

		if (lhsData[i] < rhsData[i])
			return -1;
	}

	return 0;
}

// const fucks up loop optimization on release
void LINTLshift(u32 *dst, /* const */ u32 *src, u32 shift)
{
	// i being int here just fucks up release in general
	u32 i;

	u32 size = src[0];

	u32 *srcData = src + 1;
	u32 *dstData = dst + 1;

	u32 bigShift = shift / ULONG_BIT;
	u32 smallShift = shift % ULONG_BIT;

	u64 num = 0;

	for (i = 0; i < bigShift; i++)
		dstData[i] = 0;


	for (i = 0; i < size; i++)
	{
		num += (u64)srcData[i] << smallShift;

		dstData[i + bigShift] = num & ULONG_MAX;
		num = (num >> ULLONG_ULONG_BIT_DIFF) & ULONG_MAX;
	}

	dstData[i + bigShift] = num;
	*dst = size + bigShift;

	if (num)
		(*dst)++;
}

int LINTMsb(const u32 *data)
{
	int i;

	u32 size = data[0];

	u32 last = LINTNextElement(data, size - 1);
	u32 msbPos = ULONG_BIT;
	u32 a;

	i = 0;
	while (i < ULONG_BIT)
	{
		if (((1ul << (ULONG_BIT - 1)) >> i) & last)
			break;

		i++;
		a = msbPos--; // ?
	}

	return msbPos + (size - 1) * ULONG_BIT;
}

void LINTSub(u32 *dst, const u32 *lhs, const u32 *rhs)
{
	int i;

	u32 lhsSize = lhs[0];
	u32 rhsSize = rhs[0];

	const u32 *lhsData = lhs + 1;
	const u32 *rhsData = rhs + 1;
	u32 *dstData = dst + 1;

	u64 num = 0;

	for (i = 0; i < lhsSize; i++)
	{
		dstData[i] = lhsData[i] - (ULONG)num;

		if ((u64)dstData[i] > ULONG_MAX - num)
			num = 1;
		else
			num = 0;

		if (i < rhsSize)
			dstData[i] -= rhsData[i];

		if (dstData[i] > -1l - rhsData[i])
			num++;
	}

	i = lhsSize;
	while (i && !dstData[i])
		i--;

	*dst = i + 1;
}

// TODO on release
void LINTMul(u32 *dst, const u32 *lhs, const u32 *rhs)
{
	int i, j;

	const u32 lhsSize = lhs[0];
	const u32 rhsSize = rhs[0];

	const u32 *lhsData = lhs + 1;
	const u32 *rhsData = rhs + 1;
	u32 *dstData = dst + 1;
	u32 a; // ?

	u64 num = 0;

	dst[0] = 1;

	memset(dst + 1, 0, 128); // where is 128 from?

	// buffer was cleared
	if ((lhs[0] == 1 && lhs[1] == 0) || (rhs[0] == 1 && rhs[1] == 0))
		return;

	for (i = 0; i < rhsSize; i++)
	{
		num = 0;

		for (j = 0; j < lhsSize; j++)
		{
			num = (u64)lhsData[j] * rhsData[i] + num
			    + dstData[i + j];

			dstData[i + j] = num & ULONG_MAX;
			num = ((num >> ULLONG_ULONG_BIT_DIFF) & ULONG_MAX)
			    % (1ull << ULLONG_ULONG_BIT_DIFF);
		}

		dstData[i + j] = num;
	}

	if (num == 0)
		a = *dst = lhsSize + rhsSize - 1;
	else
		a = *dst = lhsSize + rhsSize;
}
