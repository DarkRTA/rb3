#ifndef UTL_TIMECONVERSION_H
#define UTL_TIMECONVERSION_H

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

#endif
