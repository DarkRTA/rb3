#pragma once
#include "obj/Object.h"
#include "meta/FixedSizeSaveable.h"
#include "tour/TourGameRules.h"

class BandProfile;

class GamerAwardStatus : public FixedSizeSaveable {
public:
    GamerAwardStatus();
    virtual ~GamerAwardStatus();
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    static int SaveSize(int);

    int unk8; // 0x8
    int unkc; // 0xc
    bool unk10; // 0x10
};

class AccomplishmentProgress : public Hmx::Object, public FixedSizeSaveable {
public:
    AccomplishmentProgress(BandProfile*);
    virtual ~AccomplishmentProgress();
    virtual DataNode Handle(DataArray*, bool);
    virtual void SaveFixed(FixedSizeSaveableStream&) const;
    virtual void LoadFixed(FixedSizeSaveableStream&, int);

    void Clear();
    int GetToursPlayed(Symbol) const;
    void UpdateTourPlayedForAllParticipants(Symbol);
    int GetToursGotAllStars(Symbol) const;
    void SetToursGotAllStars(Symbol, int);
    int GetQuestCompletedCount(TourGameType) const;
    void SetQuestCompletedCount(TourGameType, int);
    bool AddAccomplishment(Symbol);
    bool IsAccomplished(Symbol) const;
    void NotifyPlayerOfAccomplishment(Symbol, const char*);
    void NotifyPlayerOfCategoryComplete(Symbol);
    void NotifyPlayerOfGroupComplete(Symbol);
    bool AddAward(Symbol, Symbol);
    void Poll();
    void UpdateTourPlayed(Symbol);
    void UpdateMostStars(Symbol, int);
    int GetCurrentValue(Symbol);
    void ClearStepTrackingMap();
    void SetCurrentValue(Symbol, int);
    int GetNumCompleted() const;
    bool HasNewAwards() const;
    Symbol GetFirstNewAwardReason() const;
    Symbol GetFirstNewAward() const;
    void ClearFirstNewAward();
    bool HasNewRewardVignettes() const;
    Symbol GetFirstNewRewardVignette() const;
    void ClearFirstNewRewardVignette();
    bool HasNewRewardVignetteFestival() const;
    void ClearNewRewardVignetteFestival();
    int GetNumCompletedInCategory(Symbol) const;
    int GetNumCompletedInGroup(Symbol) const;
    void SetMetaScore(int);
    void AddNewRewardVignette(Symbol);
    bool IsUploadDirty() const;
    bool HasAward(Symbol) const;

    static int SaveSize(int);

    std::map<Symbol, int> unk24; // 0x24
    BandProfile* mParentProfile; // 0x3c
    bool unk40; // 0x40
    std::list<GamerAwardStatus*> unk44; // 0x44
    std::set<Symbol> unk4c; // 0x4c
    std::set<Symbol> unk64; // 0x64
    std::vector<int> unk7c; // 0x7c
    int unk84; // 0x84
    std::set<Symbol> unk88; // 0x88
    std::list<std::pair<Symbol, Symbol> > unka0; // 0xa0
    std::list<Symbol> unka8; // 0xa8
    std::set<Symbol> unkb0; // 0xb0
    int unkc8; // 0xc8
    int unkcc; // 0xcc
    int unkd0; // 0xd0
    int unkd4; // 0xd4
    int unkd8; // 0xd8
    int unkdc; // 0xdc
    int unke0; // 0xe0
    int unke4; // 0xe4
    int unke8; // 0xe8
    int unkec; // 0xec
    int unkf0[11][4]; // 0xf0
    int unk1a0[11][4]; // 0x1a0
    int unk250[11][4]; // 0x250
    int unk300[11][4]; // 0x300
    int unk3b0[11]; // 0x3b0
    int unk3dc; // 0x3dc
    int unk3e0[11]; // 0x3e0
    int unk40c[11]; // 0x40c
    int unk438[11]; // 0x438
    int unk464[11]; // 0x464
    int unk490[11]; // 0x490
    int unk4bc[11]; // 0x4bc
    int unk4e8[11]; // 0x4e8
    int unk514[11]; // 0x514
    int unk540[11]; // 0x540
    int unk56c[4]; // 0x56c
    int unk57c[4]; // 0x57c
    int unk58c[4]; // 0x58c
    int unk59c[4]; // 0x59c
    int unk5ac[4]; // 0x5ac
    int unk5bc[4]; // 0x5bc
    int unk5cc[4]; // 0x5cc
    int unk5dc; // 0x5dc
    int unk5e0; // 0x5e0
    std::map<Symbol, int> unk5e4; // 0x5e4
    std::map<Symbol, int> unk5fc; // 0x5fc
    std::map<Symbol, int> unk614; // 0x614
    std::map<int, int> unk62c; // 0x62c
    bool unk644; // 0x644
    bool unk645; // 0x645
    int unk648; // 0x648
};