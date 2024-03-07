#include "utl/BeatMap.h"

BeatMap gDefaultBeatMap;
BeatMap* TheBeatMap = &gDefaultBeatMap;

void SetTheBeatMap(BeatMap* bmap){
    TheBeatMap = bmap;
}

void ResetTheBeatMap(){
    TheBeatMap = &gDefaultBeatMap;
}

bool BeatInfoCmp(const BeatInfo& info, int i){
//       return ((int)(param_2 ^ *(uint *)param_1) >> 1) - ((param_2 ^ *(uint *)param_1) & param_2) >> 0x1f;
}

BeatMap::BeatMap(){
    
}
