#include "utl/TimeConversion.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "utl/BeatMap.h"
#include "utl/TempoMap.h"

static DataNode OnSecondsToBeat(DataArray* msg){
    return DataNode(SecondsToBeat(msg->Float(1)));
}

static DataNode OnBeatToSeconds(DataArray* msg){
    return DataNode(BeatToSeconds(msg->Float(1)));
}

static DataNode OnBeatToMs(DataArray* msg){
    return DataNode(BeatToMs(msg->Float(1)));
}

static DataNode OnMsToTick(DataArray* msg){
    return DataNode(MsToTick(msg->Float(1)));
}

void TimeConversionInit(){
    DataRegisterFunc("seconds_to_beat", OnSecondsToBeat);
    DataRegisterFunc("beat_to_seconds", OnBeatToSeconds);
    DataRegisterFunc("beat_to_ms", OnBeatToMs);
    DataRegisterFunc("ms_to_tick", OnMsToTick);
}

#pragma push
#pragma force_active on
inline float MsToTick(float f){
    return TheTempoMap->TimeToTick(f);
}

inline float MsToBeat(float f){
    return TheBeatMap->Beat(TheTempoMap->TimeToTick(f));
}

inline float TickToMs(float f){
    return TheTempoMap->TickToTime(f);
}
#pragma pop

float TimeConversionLol(float f){
    return MsToBeat(TickToMs(f));
}

#pragma push
#pragma force_active on
inline float BeatToMs(float f){
    return TheTempoMap->TickToTime(TheBeatMap->BeatToTick(f));
}
#pragma pop

float BeatToTick(float f){
    return TheBeatMap->BeatToTick(f);
}

float TickToBeat(int i){
    return TheBeatMap->Beat(i);
}

#pragma push
#pragma force_active on
inline float SecondsToBeat(float f){
    return MsToBeat(f * 1000.0f);
}
#pragma pop

float TickToSeconds(float f){
    return TickToMs(f) / 1000.0f;
}

#pragma push
#pragma force_active on
inline float BeatToSeconds(float f){
    return BeatToMs(f) / 1000.0f;
}
#pragma pop