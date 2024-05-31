#include "synth/Mic.h"
#include "obj/Data.h"
#include "os/Debug.h"

#include "decomp.h"

void Mic::Set(const DataArray* data){
    MILO_ASSERT(data, 0x12);
    SetGain(data->FindArray("gain", true)->Float(1));
    SetDMA(data->FindArray("dma", true)->Int(1) != 0);
    DataArray* compressorArr = data->FindArray("compressor", true);
    SetCompressor(compressorArr->Int(1) != 0);
    SetCompressorParam(compressorArr->Float(2));
}

DECOMP_FORCEFUNC(Mic, Mic, GetDroppedSamples())
DECOMP_FORCEFUNC(Mic, Mic, IsPlaying())

const char* unusedmicstrings[] = { "mBuffer", "len <= mSize"};
