#ifndef UTL_CHUNKIDS_H
#define UTL_CHUNKIDS_H
#include <string.h>

class ChunkID {
public:
    char mStr[4];
    ChunkID(){
        memcpy(mStr, "????", 4);
    }
    ChunkID(const char* str){
        memcpy(mStr, str, 4);
    }
};

extern ChunkID kListChunkID;
extern ChunkID kRiffChunkID;
extern ChunkID kMidiChunkID;
extern ChunkID kMidiHeaderChunkID;
extern ChunkID kMidiTrackChunkID;
extern ChunkID kWaveChunkID;
extern ChunkID kWaveFormatChunkID;
extern ChunkID kWaveDataChunkID;
extern ChunkID kWaveFactChunkID;
extern ChunkID kWaveInstChunkID;
extern ChunkID kWaveSampleChunkID;
extern ChunkID kWaveCueChunkID;
extern ChunkID kWaveLabelChunkID;
extern ChunkID kWaveTextChunkID;
extern ChunkID kWaveAdditionalChunkID;

#endif
