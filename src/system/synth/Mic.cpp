#include "synth/Mic.h"
#include "obj/Data.h"
#include "os/Debug.h"


void Mic::Set(const DataArray* data){
    MILO_ASSERT(data, 0x12);
    SetGain(data->FindArray("gain", true)->Float(1));
    SetDMA(data->FindArray("dma", true)->Int(1) != 0);
    DataArray* compressorArr = data->FindArray("compressor", true);
    SetCompressor(compressorArr->Int(1) != 0);
    SetCompressorParam(compressorArr->Float(2));
}

void beesechurger(Mic* mic){
    mic->IsPlaying();
    mic->GetDroppedSamples();
    const char* unusedmicstrings[] = { "mBuffer", "len <= mSize"};
}
