#pragma once
#include "utl/Symbol.h"
#include "utl/BinStream.h"
#include <vector>

class MatchmakingSettings {
public:
    MatchmakingSettings(){}
    virtual ~MatchmakingSettings(){}
    virtual void SetMode(Symbol, int);
    virtual void SetRanked(bool b){ mRanked = b; }
    virtual void AddCustomSetting(int, int);

    void ClearCustomSettings();
    int NumCustomSettings() const;
    int GetCustomID(int) const;
    int GetCustomValue(int) const;
    int GetCustomValueByID(int) const;
    void Save(BinStream&) const;
    void Load(BinStream&);

    Symbol mModeName; // 0x4
    int mModeFilter; // 0x8
    bool mRanked; // 0xc
    std::vector<int> mCustomIDs; // 0x10
    std::vector<int> mCustomValues; // 0x18
};