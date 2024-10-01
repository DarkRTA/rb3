#include "radmem.h"
#include <stdlib.h>

malloc_func usermalloc = NULL;
free_func userfree = NULL;

void RADSetMemory(malloc_func malloc, free_func free) {
    usermalloc = malloc;
    userfree = free;
}

void *radmalloc(u32 size) {
    if (size == 0 || size == -1) {
        return NULL;
    } else {
        if (usermalloc != NULL) {
            usermalloc(size + 0x40);
        } else {
            void* mem = malloc(size + 0x40);
            if (mem == NULL) return NULL;
        }
    }
}

void radfree(void* mem) {
    if (!mem) return;
    if (((u8*)mem)[-2] == 3) {
        (*(free_func)*((u8**)mem - 3))((u8*)mem - ((u8*)mem)[-1]);
        return;
    }
    free((u8*)mem - ((u8*)mem)[-1]);
}
