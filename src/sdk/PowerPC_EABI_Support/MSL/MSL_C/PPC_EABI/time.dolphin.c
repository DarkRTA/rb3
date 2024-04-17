#include "revolution/OS.h"
#include "types.h"

u64 __get_clock(void) {
    unsigned int x = OSGetTick();
    return x;
}
