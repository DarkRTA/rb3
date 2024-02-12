#ifndef TRK_NUBEVENT
#define TRK_NUBEVENT

#include "MetroTRK/dstypes.h"
#include "MetroTRK/trk.h"
#include "MetroTRK/msgbuf.h"

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
