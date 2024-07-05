#include "types.h"
#include "mem_funcs.h"

void* memmove(void* dst, const void* src, size_t n) {
    char* dst2 = dst; char* src2 = *(char**)&src;
    uint r6 = (uint)dst ^ (uint)src;
    uint r7 = ((uint)dst << __cntlzw(r6)) >> 31;
    if (n >= 0x20) {
        if (r6 & 3) {
            if (r7 == 0) {
                __copy_longs_unaligned(dst, src, n);
            } else __copy_longs_rev_unaligned(dst, src, n);
        } else {
            if (r7 == 0) {
                __copy_longs_aligned(dst, src, n);
            } else __copy_longs_rev_aligned(dst, src, n);
        }
        return dst;
    } else {
        if (r7 == 0) {
            src2--; 
            dst2--; 
            n++;
            while (--n) *++dst2 = *++src2;
        } else {
            src2 += n;
            dst2 += n;
            n++;
            while (--n) *--dst2 = *--src2;
        }
        return dst;
    }
    //while (n--) {}
}

void* memchr(const void* mem, int c, size_t n) {
    u8 c2 = c;
    char* m2 = *(char**)&mem - 1;
    n++;
    while (--n) if (*(u8*)(++m2) == c2) return m2;
    return NULL;
}

void* __memrchr(const void* mem, uint c, size_t n) {
    u8 c2 = c;
    char* m2 = *(char**)&mem + n;
    n++;
    while (--n) if (*(u8*)(--m2) == c2) return m2;
    return NULL;
}

int memcmp(const void* src1, const void* src2, size_t n) {
    const u8 *p1;
	const u8 *p2;

	for (p1 = (const u8 *)src1 - 1, p2 = (const u8 *)src2 - 1, n++; --n;)
	{
		if (*++p1 != *++p2)
		{
			return (*p1 < *p2) ? -1 : 1;
		}
	}
    return 0;
}
