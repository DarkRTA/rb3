#pragma once
#include "AccomplishmentSongConditional.h"
#include "obj/Data.h"

class AccomplishmentSongListConditional : public AccomplishmentSongConditional {
public:
    AccomplishmentSongListConditional(DataArray*, int);
    virtual ~AccomplishmentSongListConditional();
    virtual AccomplishmentType GetType() const;
    virtual bool IsFulfilled(BandProfile*) const;
    virtual bool IsRelevantForSong(Symbol) const;
    virtual bool InqIncrementalSymbols(BandProfile*, std::vector<Symbol>&) const;    
    virtual bool HasSpecificSongsToLaunch() const;
    virtual int GetNumCompletedSongs(BandProfile*) const;
    virtual int GetTotalNumSongs() const;

    void Configure(DataArray*);

    std::vector<Symbol> unk7c; // 0x7c
    std::set<Symbol> unk84; // 0x84
};