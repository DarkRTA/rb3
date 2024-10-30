#pragma once
#include "net/Synchronize.h"
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

class SessionSettings : public MatchmakingSettings, public Synchronizable {
public:
    SessionSettings();
    virtual ~SessionSettings(){}
    virtual void SetMode(Symbol, int);
    virtual void SetRanked(bool);
    virtual void AddCustomSetting(int, int);
    virtual void SyncSave(BinStream&, unsigned int) const;
    virtual void SyncLoad(BinStream&, unsigned int);
    virtual bool HasSyncPermission() const;
    virtual void OnSynchronizing(unsigned int);
    virtual void OnSynchronized(unsigned int);

    void Clear();
    void SetPublic(bool);

    bool mPublic; // 0x3c
};

class SearchSettings : public MatchmakingSettings {
public:
    SearchSettings(int, bool, int);
    virtual ~SearchSettings(){}

    int mQueryID; // 0x20
};