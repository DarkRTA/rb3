#ifndef TRK_MSG
#define TRK_MSG

#include "MetroTRK/dstypes.h"
#include "MetroTRK/trk.h"
#include "MetroTRK/msgbuf.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct TRKPacketSeq {
	ui16 unk0;
	ui8 unk2[6];
} TRKPacketSeq;

DSError TRK_MessageSend(MessageBuffer*);

#ifdef __cplusplus
}
#endif
#endif
