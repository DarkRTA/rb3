#ifndef RB3_MATCHMAKINGSETTINGS_H
#define RB3_MATCHMAKINGSETTINGS_H
#include "symbol.hpp"
#include "binstream.hpp"

class MatchmakingSettings {
public:
	virtual ~MatchmakingSettings(); // fn_800A7844
	virtual void SetMode(Symbol, int); // fn_800A71BC
	virtual void SetRanked(bool); // fn_800A7DE0
	virtual void AddCustomSetting(int, int); // fn_800A71FC

	void ClearCustomSettings();
	void NumCustomSettings() const;
	// unknown return type GetCustomID(int) const
	// unknown return type GetCustomValue(int) const
	// unknown return type GetCustomValueByID(int) const

	void Save(BinStream&) const;
	void Load(BinStream&);

	Symbol unk4;
	unsigned int unk8;
	bool unkc;
	void* unk10; //some currently unknown class
};

#endif
