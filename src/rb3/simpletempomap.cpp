#include "simpletempomap.hpp"

// fn_8037A49C
SimpleTempoMap::SimpleTempoMap(float f)
{
	ms_per_tick = f / 480.0f;
}

// fn_8037A4FC
double SimpleTempoMap::TickToTime(float f) const
{
	return f * ms_per_tick;
}

// fn_8037A508
double SimpleTempoMap::TimeToTick(float f) const
{
	return f / ms_per_tick;
}

// fn_8037A514
float SimpleTempoMap::GetTempo(int i) const
{
	return 480.0f * ms_per_tick;
}

// fn_8037A528
double SimpleTempoMap::GetTempoBPM(int i) const
{
	return 60000.0f / (480.0f * ms_per_tick);
}

// fn_8037A548
int SimpleTempoMap::GetTempoUSecs(int i)
{
	return GetTempo(i) * 1000.0f;
}