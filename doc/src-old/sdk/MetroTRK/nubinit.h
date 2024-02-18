#ifndef TRK_NUBINIT
#define TRK_NUBINIT

#include "MetroTRK/dstypes.h"
#include "MetroTRK/trk.h"

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
