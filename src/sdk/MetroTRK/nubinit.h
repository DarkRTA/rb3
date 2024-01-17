#ifndef TRK_NUBINIT
#define TRK_NUBINIT

#include "sdk/MetroTRK/dstypes.h"
#include "sdk/MetroTRK/trk.h"

#ifdef __cplusplus
extern "C"{
#endif

extern bool gTRKBigEndian;

DSError TRK_InitializeNub(void);
DSError TRK_TerminateNub(void);
void TRK_NubWelcome(void);

#ifdef __cplusplus
}
#endif
#endif
