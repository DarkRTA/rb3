#include "revolution/os/OSInterrupt.h"
#include "types.h"

void MWInitializeCriticalSection(u32* critsect) {}

void MWEnterCriticalSection(u32* critsect) { *critsect = OSDisableInterrupts(); }

void MWExitCriticalSection(u32* critsect) { OSRestoreInterrupts(*critsect); }
