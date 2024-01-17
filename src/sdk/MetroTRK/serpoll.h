#ifndef TRK_SERPOLL
#define TRK_SERPOLL

#include "sdk/MetroTRK/dstypes.h"
#include "sdk/MetroTRK/trk.h"

#ifdef __cplusplus
extern "C"{
#endif

extern void* gTRKInputPendingPtr;

void TRKGetInput();
void TRKProcessInput(int);
DSError TRKInitializeSerialHandler();
DSError TRKTerminateSerialHandler();

#ifdef __cplusplus
}
#endif
#endif
