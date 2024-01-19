#ifndef TRK_MSGHNDLR
#define TRK_MSGHNDLR

#include "sdk/MetroTRK/dstypes.h"
#include "sdk/MetroTRK/trk.h"
#include "sdk/MetroTRK/msgbuf.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct CommandReply {
	ui32 unk0;
	//TODO: fix enum size shenanigans
	union{
		ui8 commandId;
		MessageCommandID commandIdInt;
	};
	union{
	    ui8 replyError;
        DSReplyError replyErrorInt;
    };
	ui32 unkC;
	ui8 unk10[0x30];
} CommandReply;

bool GetTRKConnected();
DSError TRK_DoConnect(MessageBuffer*);
DSError TRKDoDisconnect(MessageBuffer*);
DSError TRKDoReset(MessageBuffer*);
DSError TRKDoVersions(MessageBuffer*);
DSError TRKDoSupportMask(MessageBuffer*);
DSError TRKDoOverride(MessageBuffer*);
DSError TRKDoReadMemory(MessageBuffer*);
DSError TRKDoWriteMemory(MessageBuffer*);
DSError TRKDoReadRegisters(MessageBuffer*);
DSError TRKDoWriteRegisters(MessageBuffer*);
DSError TRKDoContinue(MessageBuffer*);
DSError TRKDoStep(MessageBuffer*);
DSError TRKDoStop(MessageBuffer*);
DSError TRKDoSetOption(MessageBuffer*);


#ifdef __cplusplus
}
#endif
#endif
