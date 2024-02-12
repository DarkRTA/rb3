#ifndef TRK_TARGIMPL
#define TRK_TARGIMPL

#include "MetroTRK/dstypes.h"
#include "MetroTRK/trk.h"
#include "MetroTRK/nubevent.h"
#include "MetroTRK/msgbuf.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum ValidMemoryOptions {
	kValidMemoryReadable,
	kValidMemoryWriteable
} ValidMemoryOptions;

typedef enum MemoryAccessOptions {
	kUserMemory,
	kDebuggerMemory
} MemoryAccessOptions;

ui32 __TRK_get_MSR();

void TRKTargetSetStopped(bool);
void TRKTargetSetInputPendingPtr(void*);

DSError TRKTargetAccessMemory(void*,ui32,size_t*,MemoryAccessOptions,bool);
DSError TRKTargetAccessDefault(ui32,ui32,MessageBuffer*,size_t*,bool);
DSError TRKTargetAccessFP(ui32,ui32,MessageBuffer*,size_t*,bool);
DSError TRKTargetAccessExtended1(ui32,ui32,MessageBuffer*,size_t*,bool);
DSError TRKTargetAccessExtended2(ui32,ui32,MessageBuffer*,size_t*,bool);

DSError TRKTargetVersions(DSVersions*);
DSError TRKTargetCheckException();

void TRK_InterruptHandler();
void TRKSwapAndGo();

DSError TRKTargetInterrupt(NubEvent*);

DSError TRKTargetAddStopInfo(MessageBuffer*);
void TRKTargetAddExceptionInfo(MessageBuffer*);

DSError TRKTargetSingleStep(ui8,bool);
DSError TRKTargetStepOutOfRange(ui32,ui32,bool);

ui32 TRKTargetGetPC();

DSError TRKTargetSupportRequest();
DSError TRKTargetFlushCache(ui32,ui32,ui32);

bool TRKTargetStopped();
void TRKTargetSetStopped(bool);
DSError TRKTargetStop();

void TRKTargetSetInputPendingPtr(void*);

#ifdef __cplusplus
}
#endif
#endif
