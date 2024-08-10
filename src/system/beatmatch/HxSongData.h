#ifndef BEATMATCH_HXSONGDATA_H
#define BEATMATCH_HXSONGDATA_H
#include "beatmatch/SongPos.h"

// forward decs
class TempoMap;
class BeatMap;
class MeasureMap;

class HxSongData {
public:
    HxSongData(){}
    virtual ~HxSongData(){}
    virtual SongPos CalcSongPos(float) = 0;
    virtual TempoMap* GetTempoMap() const = 0;
    virtual BeatMap* GetBeatMap() const = 0;
    virtual MeasureMap* GetMeasureMap() const = 0;
};

#endif
