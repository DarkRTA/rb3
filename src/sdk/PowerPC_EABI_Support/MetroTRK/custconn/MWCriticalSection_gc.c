#include "revolution/os/OSInterrupt.h"
#include "types.h"

void MWInitializeCriticalSection(BOOL* critsect) {}

void MWEnterCriticalSection(BOOL* critsect) { *critsect = OSDisableInterrupts(); }

void MWExitCriticalSection(BOOL* critsect) { OSRestoreInterrupts(*critsect); }
