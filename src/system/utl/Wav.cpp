#include "utl/Wav.h"
#include "decomp.h"
#include "milo_types.h"
#include "os/Debug.h"
#include "os/Endian.h"
#include "os/File.h"
#include <cstring>

namespace {
    const char *riffID = "RIFF";
    const char *waveID = "WAVE";
    const char *formatID = "fmt ";
    const char *dataID = "data";
}

void WriteWav(const char *fname, int, const void *, int) {
    int buf[8];
    int fd = FileOpen(fname, 0xA04);
    MILO_ASSERT(fd >= 0, 87);
    memcpy(&buf[6], ::riffID, 4);
    FileWrite(fd, &buf[6], 8);
    memcpy(&buf[1], ::waveID, 4);
    FileWrite(fd, &buf[1], 4);
    buf[5] = 0x10000000;
    memcpy(&buf[4], ::formatID, 4);
    FileWrite(fd, &buf[4], 8);

    FileClose(fd);
}

#pragma push
#pragma dont_inline on
DECOMP_FORCEBLOCK(Wav, (void), uint x = 2; uint& ui = x; EndianSwapEq(ui);)
DECOMP_FORCEBLOCK(Wav, (void), ushort x = 2; ushort& us = x; EndianSwapEq(us);)
DECOMP_FORCEBLOCK(Wav, (void), short x = 2; short& ui = x; EndianSwapEq(ui);)
#pragma pop
