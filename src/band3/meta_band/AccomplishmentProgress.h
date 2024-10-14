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
    void AddAward(Symbol, Symbol);
    void Poll();

    static int SaveSize(int);

    std::map<Symbol, int> unk24; // 0x24
    BandProfile* mParentProfile; // 0x3c
    int unk40; // 0x40
    std::list<int> unk44; // 0x44
    std::set<Symbol> unk4c; // 0x4c
    std::set<Symbol> unk64; // 0x64
    std::vector<int> unk7c; // 0x7c
    int unk84; // 0x84
    std::set<Symbol> unk88; // 0x88
    std::list<std::pair<Symbol, Symbol> > unka0;
    std::list<Symbol> unka8; // 0xa8
    std::set<Symbol> unkb0; // 0xb0
    char filler[0x51c];
    std::map<Symbol, int> unk5e4; // 0x5e4
    std::map<Symbol, int> unk5fc; // 0x5fc
    std::map<Symbol, int> unk614; // 0x614
    std::map<int, int> unk62c; // 0x62c
    bool unk644; // 0x644
    int unk648; // 0x648
};