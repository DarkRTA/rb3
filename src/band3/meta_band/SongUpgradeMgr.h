#pragma once
#include "os/ContentMgr.h"
#include "utl/BinStream.h"
#include <set>
#include <map>
#include "utl/Str.h"
#include "obj/Data.h"

class SongUpgradeData {
public:
    SongUpgradeData();
    SongUpgradeData(DataArray*);

    void InitSongUpgradeData();
    int RealGuitarTuning(int) const;
    int RealBassTuning(int) const;
    float Rank(Symbol) const;
    const char* MidiFile() const;
    void Save(BinStream&);
    void Load(BinStream&);
    bool HasPart(Symbol) const;
    bool CorrectMidiFile(ContentLocT, Symbol);

    static int sSaveVer;

    int mUpgradeVersion; // 0x0
    String mMidiFile; // 0x4
    float mRealGuitarRank; // 0x10
    float mRealBassRank; // 0x14
    int mRealGuitarTuning[6]; // 0x18
    int mRealBassTuning[4]; // 0x30
};

class SongUpgradeMgr : public ContentMgr::Callback {
public:
    SongUpgradeMgr();
    virtual ~SongUpgradeMgr(){}
    virtual void ContentStarted();
    virtual bool ContentDiscovered(Symbol);
    virtual void ContentMounted(const char*, const char*);
    virtual void ContentLoaded(class Loader*, ContentLocT, Symbol);
    virtual const char* ContentPattern();
    virtual const char* ContentDir();

    bool HasUpgrade(int) const;
    const char* ContentName(int) const;
    SongUpgradeData* UpgradeData(int) const;

    std::set<int> unk4; // 0x4
    std::map<int, SongUpgradeData*> unk1c; // 0x1c
    std::map<Symbol, std::vector<int> > unk34; // 0x34
    std::map<int, Symbol> unk4c; // 0x4c
    bool unk64; // 0x64
};