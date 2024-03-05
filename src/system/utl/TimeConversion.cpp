#include "utl/TimeConversion.h"
#include "obj/Data.h"
#include "obj/DataFunc.h"
#include "utl/BeatMap.h"
#include "utl/TempoMap.h"

static DataNode OnSecondsToBeat(DataArray* msg){
    return DataNode(TheBeatMap->Beat(TheTempoMap->TimeToTick(msg->Float(1) * 1000.0f)));
}

static DataNode OnBeatToSeconds(DataArray* msg){
    return DataNode(TheTempoMap->TickToTime(TheBeatMap->BeatToTick(msg->Float(1))) / 1000.0f);
}

static DataNode OnBeatToMs(DataArray* msg){
    return DataNode(TheTempoMap->TickToTime(TheBeatMap->BeatToTick(msg->Float(1))));
}

static DataNode OnMsToTick(DataArray* msg){
    return DataNode(TheTempoMap->TimeToTick(msg->Float(1)));
}

void TimeConversionInit(){
    DataRegisterFunc("seconds_to_beat", OnSecondsToBeat);
    DataRegisterFunc("beat_to_seconds", OnBeatToSeconds);
    DataRegisterFunc("beat_to_ms", OnBeatToMs);
    DataRegisterFunc("ms_to_tick", OnMsToTick);
}

float MsToTick(float f){
    return TheTempoMap->TimeToTick(f);
}

float MsToBeat(float f){
    return TheBeatMap->Beat(TheTempoMap->TimeToTick(f));
}

float TickToMs(float f){
    return TheTempoMap->TickToTime(f);
}

float BeatToMs(float f){
    return TheTempoMap->TickToTime(TheBeatMap->BeatToTick(f));
}

float BeatToTick(float f){
    return TheBeatMap->BeatToTick(f);
}

float TickToBeat(int i){
    return TheBeatMap->Beat(i);
}

float SecondsToBeat(float f){
    return TheBeatMap->Beat(TheTempoMap->TimeToTick(f * 1000.0f));
}

float TickToSeconds(float f){
    return TheTempoMap->TickToTime(f) / 1000.0f;
}

float BeatToSeconds(float f){
    return TheTempoMap->TickToTime(TheBeatMap->BeatToTick(f)) / 1000.0f;
}
