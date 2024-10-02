#include "radmem.h"
#include "types.h"
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
        void* mem;
        u8 offset;
        u32 mode;
        if (usermalloc != NULL) {
            mem = usermalloc(size + 0x40);
            if ((u32)mem == 0) goto user_malloc_failed;
            if ((s32)mem == -1) {
                return NULL;
            }
            mode = 3;
        } else {
            user_malloc_failed:
            mem = malloc(size + 0x40);
            if (mem == NULL) return NULL;
            mode = 0;
        }
        
        offset = (u8)(0x40 - ((u32)mem & 0x1F));
        mem = (void*)((u32)mem + offset);
        *((u8*)mem - 1) = offset;
        *((u8*)mem - 2) = mode;
        if (mode == 3) *((free_func*)mem - 3) = userfree;
        return mem;
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
