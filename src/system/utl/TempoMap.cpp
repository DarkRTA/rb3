#include "utl/SimpleTempoMap.h"
#include "utl/TempoMap.h"

SimpleTempoMap gDefaultTempoMap(1000.0f);
TempoMap* TheTempoMap = &gDefaultTempoMap;

void SetTheTempoMap(TempoMap* tmap){
    TheTempoMap = tmap;
}

void ResetTheTempoMap(){
    TheTempoMap = &gDefaultTempoMap;
}

float SimpleTempoMap::GetTimeInLoop(float time){
    return time;
}

int SimpleTempoMap::GetLoopTick(int, int&) const {
    return 0;
}

int SimpleTempoMap::GetLoopTick(int) const {
    return 0;
}

void SimpleTempoMap::SetLoopPoints(int, int){

}

void SimpleTempoMap::ClearLoopPoints(){

}

int SimpleTempoMap::GetTempoChangePoint(int) const {
    return 0;
}

int SimpleTempoMap::GetNumTempoChangePoints() const {
    return 1;
}

int SimpleTempoMap::GetTempoInMicroseconds(int i) const {
    return GetTempo(i) * 1000.0f;
}

float SimpleTempoMap::GetTempo(int) const {
    return 480.0f * mTempo;
}

float SimpleTempoMap::GetTempoBPM(int) const {
    return 60000.0f / (480.0f * mTempo);
}

float SimpleTempoMap::TimeToTick(float f) const {
    return f / mTempo;
}

float SimpleTempoMap::TickToTime(float f) const {
    return f * mTempo;
}
