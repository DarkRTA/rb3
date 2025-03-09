#include "types.h"

uint __AXProfile;
uint __AXMaxProfiles;
uint __AXCurrentProfile;
BOOL __AXProfileInitialized;

int __AXGetCurrentProfile(void) {
    if (__AXProfileInitialized) {
        int profile = __AXCurrentProfile;
        __AXCurrentProfile++;
        __AXCurrentProfile %= __AXMaxProfiles;
        return __AXProfile + (__AXMaxProfiles * 56);
    } else
        return 0;
}