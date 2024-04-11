#include "utl/WaveFile.h"

WaveFile::WaveFile(BinStream& bs) : mMarkers(), mRiffList(bs, true) {
    ReadFormat();
    ReadMarkers();
    ReadNumSamples();
}

WaveFile::~WaveFile(){

}

WaveFileData::WaveFileData(WaveFile& wf) : IDataChunk(wf.PrepareToProvideData()), mWaveFile(&wf) {
    
}
