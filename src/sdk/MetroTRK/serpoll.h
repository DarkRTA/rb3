#ifndef TRK_SERPOLL
#define TRK_SERPOLL

#include "MetroTRK/dstypes.h"
#include "MetroTRK/trk.h"

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
