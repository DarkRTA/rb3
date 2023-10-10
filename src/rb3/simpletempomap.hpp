#ifndef RB3_SIMPLETEMPOMAP_HPP
#define RB3_SIMPLETEMPOMAP_HPP
#include "tempomap.hpp"

class SimpleTempoMap : TempoMap {
public:
	SimpleTempoMap(float); // fn_8037A49C
	virtual ~SimpleTempoMap(); // fn_8037A410
	virtual double TickToTime(float) const; // fn_8037A4FC
	virtual double TimeToTick(float) const; // fn_8037A508
	virtual float GetTempo(int) const; // fn_8037A514
	virtual int GetTempoUSecs(int i); // fn_8037A548
	virtual double GetTempoBPM(int) const; // fn_8037A528
	virtual int GetNumTempoChangePoints()
		const; // fn_8000F90C, returns 1 - GetNumTempoChangePoints
	virtual int GetTempoChangePoint(int)
		const; // links to fn_8077BAA0, which returns 0 - GetTempoChangePoint

	virtual void V_Unk10(); // links to fn_8076F540, which returns void
	virtual void V_Unk11(int, int); // links to fn_8076F540, which returns void
	virtual int V_Unk12(int, int *); // links to fn_8077BAA0, which returns 0
	virtual int V_Unk13(int, int *); // links to fn_8077BAA0, which returns 0
	virtual void V_Unk14(); // links to fn_8076F540, which returns void

	float ms_per_tick;
};

#endif
