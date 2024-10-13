#pragma once
#include "TourDesc.h"
#include "obj/Object.h"
#include "tour/TourProgress.h"
#include "tour/TourProperty.h"
#include "utl/Symbol.h"
#include "meta/SongMgr.h"
#include "game/BandUserMgr.h"
#include "tour/Quest.h"
#include "tour/TourPerformer.h"

class Tour : public Hmx::Object {
public:
    Tour(DataArray*, const SongMgr&, BandUserMgr&, bool);
    virtual ~Tour();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);

    bool HasTourProperty(Symbol) const;
    TourProperty* GetTourProperty(Symbol) const;
    void UpdateProgressWithCareerData();
    TourDesc* GetTourDesc(Symbol) const;
    Symbol GetTourStatusForStarCount(int, int) const;
    int GetStarsForTourStatus(Symbol) const;
    bool DoesTourStatusExist(int, int) const;
    const std::map<Symbol, TourProperty*>& TourProperties() const { return mTourProperties; }
    TourProgress* GetTourProgress() const;
    Quest* GetQuest();

    SongMgr* unk1c;
    BandUserMgr* unk20;
    TourPerformerImpl* unk24; // 0x24
    int unk28;
    std::map<Symbol, TourProperty*> mTourProperties; // 0x2c
};

extern Tour* TheTour;