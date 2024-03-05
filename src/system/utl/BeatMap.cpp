#include "utl/BeatMap.h"

BeatMap gDefaultBeatMap;
BeatMap* TheBeatMap = &gDefaultBeatMap;

void SetTheBeatMap(BeatMap* bmap){
    TheBeatMap = bmap;
}

void ResetTheBeatMap(){
    TheBeatMap = &gDefaultBeatMap;
}

BeatMap::BeatMap(){
    
}
