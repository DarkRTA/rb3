#include <ec/internal/shr.h>
#include <revolution/OS.h>

s64 _SHR_tick_get(void) {
    return OSGetTime();
}

s64 _SHR_ticks_to_milliseconds(u64 ticks) {
    return OSTicksToMilliseconds(ticks);
}
