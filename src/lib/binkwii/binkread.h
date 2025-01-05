#pragma once
#include "utl/BINK.h"

#ifdef __cplusplus
extern "C" {
#endif

char* BinkGetError();
void BinkSetSoundTrack(int, int);
void BinkSetVideoOnOff(BINK*, unsigned int);
BINK* BinkOpen(void*, unsigned int);
void BinkCloseTrack(BINKTRACK*);
void BinkClose(BINK*);
BINKTRACK* BinkOpenTrack(BINK*, int);

#ifdef __cplusplus
}
#endif