#include <string.h>
#include <ogg/os_types.h>

extern void *MemAllocTemp(int, int);

void *OggMalloc(int i) {
    return MemAllocTemp(i, 0);
}

void *OggCalloc(int i1, int i2) {
    void *tmp = (void *)MemAllocTemp(i1 * i2, 0);
    memset(tmp, 0, i1 * i2);
    return tmp;
}

extern void *MemRealloc(void *, int, int);

void *OggRealloc(void *v, int i) {
    return MemRealloc(v, i, 0);
}

extern void MemFree(void *);

void OggFree(void *v) {
    MemFree(v);
}
