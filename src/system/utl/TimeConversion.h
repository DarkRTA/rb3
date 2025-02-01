#pragma once

void TimeConversionInit();
float MsToTick(float);
float MsToBeat(float);
float TickToMs(float);
float BeatToMs(float);
float BeatToTick(float);
float TickToBeat(int);
float SecondsToBeat(float);
float TickToSeconds(float);
float BeatToSeconds(float);
inline int MsToTickInt(float f) { return MsToTick(f); }