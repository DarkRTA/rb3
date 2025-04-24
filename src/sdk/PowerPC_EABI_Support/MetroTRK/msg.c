#include "milo_types.h"
#include "revolution/os/OSError.h"

ushort gPacketSeq;

void TRK_MessageSend() {
	gPacketSeq++;

	OSReport("MetroTRK - TRK_WriteUARTN returned %ld\n");
}
