#include "VorbisMem.h"
#include "utl/MemMgr.h"
#include <string.h>

void* OggMalloc(int i){
    return _MemAllocTemp(i, 0);
}

void* OggCalloc(int i1, int i2){
    int mult = i1 * i2;
    void* tmp = (void*)_MemAllocTemp(mult, 0);
    memset(tmp, 0, mult);
    return tmp;
}

void* OggRealloc(void* v, int i){
    return _MemRealloc(v, i, 0);
}

void OggFree(void* v){
    _MemFree(v);
}
