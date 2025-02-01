#pragma once
#include "utl/BINK.h"

void BinkInit();
void *BinkAlloc(unsigned int);
void BinkFree(void *);
bool BinkFileOpen(BINKIO *, const char *, unsigned int);
unsigned int BinkFileReadHeader(BINKIO *, int, void *, unsigned int);
unsigned int BinkFileReadFrame(BINKIO *, unsigned int, int, void *, unsigned int);
unsigned int BinkFileGetBufferSize(BINKIO *, unsigned int);
void BinkFileSetInfo(BINKIO *, void *, unsigned int, unsigned int, unsigned int);
unsigned int BinkFileIdle(BINKIO *);
void BinkFileClose(BINKIO *);
int BinkFileBGControl(BINKIO *, unsigned int);