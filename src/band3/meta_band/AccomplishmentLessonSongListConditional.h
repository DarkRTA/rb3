#pragma once
#include "meta_band/AccomplishmentSongListConditional.h"
#include "obj/Data.h"

class AccomplishmentLessonSongListConditional : public AccomplishmentSongListConditional {
public:
    AccomplishmentLessonSongListConditional(DataArray*, int);
    virtual ~AccomplishmentLessonSongListConditional();
    virtual AccomplishmentType GetType() const;
    virtual bool CheckConditionsForSong(SongStatusMgr*, Symbol) const;

    void Configure(DataArray*);
    bool CheckLessonCompleteCondition(SongStatusMgr*, Symbol, const AccomplishmentCondition&) const;
};