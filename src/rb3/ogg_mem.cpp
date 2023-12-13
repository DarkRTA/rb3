#include <ogg/os_types.h>

extern void* MemAllocTemp(int, int);

void* OggMalloc(int i){
    return MemAllocTemp(i, 0);
}