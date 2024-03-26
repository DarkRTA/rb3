#pragma once

// #include <cstdint>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

	typedef char			sbyte;
	typedef unsigned char		ubyte;
	typedef short		sword;
	typedef unsigned short		uword;
	typedef int			sdword;
	typedef unsigned int		udword;
	typedef long long		sqword;
	typedef unsigned long long	uqword;
	typedef float				sfloat;

	#define	null	0
	#define RELEASE(x)		{ delete x;		x = null; }
	#define RELEASEARRAY(x)	{ delete[] (ubyte*)x;	x = null; }

	inline void ZeroMemory(void* addr, udword size)
	{
		memset(addr, 0, size);
	}

	inline void CopyMemory(void* dest, const void* src, udword size)
	{
		memcpy(dest, src, size);
	}

	inline void FillMemory(void* dest, udword size, ubyte val)
	{
		memset(dest, val, size);
	}

#include "RevisitedRadix.h"
#include "CustomArray.h"
#include "Adjacency.h"
#include "Striper.h"
