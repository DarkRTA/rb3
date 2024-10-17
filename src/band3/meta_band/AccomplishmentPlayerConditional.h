#pragma once
#include "AccomplishmentConditional.h"
#include "meta_band/SongSortMgr.h"
#include "obj/Data.h"

class AccomplishmentPlayerConditional : public AccomplishmentConditional {
public:
    AccomplishmentPlayerConditional(DataArray*, int);
    virtual ~AccomplishmentPlayerConditional();
    virtual AccomplishmentType GetType() const;    
    virtual bool IsFulfilled(BandProfile*) const;
    virtual bool IsRelevantForSong(Symbol) const;
    virtual bool InqProgressValues(BandProfile*, int&, int&);
    virtual void InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, BandProfile*) const;
    virtual void InitializeTrackerDesc(TrackerDesc&) const;

    void Configure(DataArray*);
    bool IsConditionMet(BandProfile*, const AccomplishmentCondition&) const;
    bool InqBestProgressValues(BandProfile*, int&, int&);
    bool InqConditionProgress(BandProfile*, const AccomplishmentCondition&, int&, int&) const;

    SongSortMgr::SongFilter mLaunchFilter; // 0x7c
    Symbol mLaunchPartDifficultySym; // 0x90
};