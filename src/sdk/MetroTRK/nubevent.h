#ifndef TRK_NUBEVENT
#define TRK_NUBEVENT

#include "sdk/MetroTRK/dstypes.h"
#include "sdk/MetroTRK/trk.h"
#include "sdk/MetroTRK/msgbuf.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef unsigned long NubEventID;

typedef enum NubEventType {
	kNullEvent,
	kShutdownEvent,
	kRequestEvent,
	kBreakpointEvent,
	kExceptionEvent,
	kSupportEvent
} NubEventType;

typedef struct NubEvent {
	NubEventType fType;
	NubEventID fID;
	MessageBufferID fMessageBufferID;
} NubEvent;

DSError TRKInitializeEventQueue();
bool TRKGetNextEvent(NubEvent*);
DSError TRKPostEvent(NubEvent*);
void TRKConstructEvent(NubEvent*, int);
void TRKDestructEvent(NubEvent*);

#ifdef __cplusplus
}
#endif
#endif
