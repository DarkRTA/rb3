#pragma once
#include "meta_band/AccomplishmentDiscSongConditional.h"
#include "obj/Data.h"

class AccomplishmentLessonDiscSongConditional : public AccomplishmentDiscSongConditional {
public:
    AccomplishmentLessonDiscSongConditional(DataArray*, int);
    virtual ~AccomplishmentLessonDiscSongConditional();
    virtual AccomplishmentType GetType() const;
    virtual bool CheckConditionsForSong(SongStatusMgr*, Symbol) const;

    void Configure(DataArray*);
    bool CheckLessonCompleteCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
};