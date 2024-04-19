#ifndef BEATMATCH_UTL_H
#define BEATMATCH_UTL_H
#include "beatmatch/TrackType.h"

class DataArray; // forward dec

enum AudioType {
    a, b, c
};

bool GemPlayableBy(int, int);
int GemNumSlots(int);
int ConsumeNumber(const char*&);
float VelocityBucketToDb(int);
AudioType TrackTypeToAudioType(TrackType);
float GetRollIntervalMs(const DataArray*, TrackType, int, bool);

#endif
