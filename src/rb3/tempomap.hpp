#ifndef RB3_TEMPOMAP_HPP
#define RB3_TEMPOMAP_HPP

class TempoMap {
public:
	TempoMap();
	virtual ~TempoMap(); // fn_8000DD10 - generic dtor
	virtual double TickToTime(float) const = 0;
	virtual double TimeToTick(float) const = 0;
	virtual float GetTempo(int) const = 0;
	virtual int GetTempoUSecs(int i) = 0;
	virtual double GetTempoBPM(int) const = 0;
	virtual int GetNumTempoChangePoints() const = 0;
	virtual int GetTempoChangePoint(int) const = 0;
	virtual void V_Unk9(); // links to fn_8076F540, which returns void
	virtual void V_Unk10() = 0;
	virtual void V_Unk11(int, int) = 0;
	virtual int V_Unk12(int, int*) = 0;
	virtual int V_Unk13(int, int*) = 0;
	virtual void V_Unk14() = 0;
};

#endif
