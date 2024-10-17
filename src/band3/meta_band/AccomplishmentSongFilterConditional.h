#pragma once
#include "AccomplishmentSongConditional.h"
#include "BandProfile.h"
#include "meta_band/SongSortMgr.h"
#include "obj/Data.h"

class AccomplishmentSongFilterConditional : public AccomplishmentSongConditional {
    AccomplishmentSongFilterConditional(DataArray*, int);
    virtual ~AccomplishmentSongFilterConditional();
    virtual AccomplishmentType GetType() const;
    virtual void UpdateIncrementalEntryName(UILabel*, Symbol);
    virtual bool IsFulfilled(BandProfile*) const;
    virtual bool IsRelevantForSong(Symbol) const;
    virtual bool InqIncrementalSymbols(BandProfile*, std::vector<Symbol>&) const;
    virtual bool IsSymbolEntryFulfilled(BandProfile*, Symbol) const;
    virtual Symbol GetFirstUnfinishedAccomplishmentEntry(BandProfile*) const;
    virtual void InitializeMusicLibraryTask(MusicLibrary::MusicLibraryTask&, BandProfile*) const;
    virtual int GetNumCompletedSongs(BandProfile*) const;
    virtual int GetTotalNumSongs() const;

    void Configure(DataArray*);
    bool InqCompletedSongs(BandProfile*, std::vector<int>&) const;
    const SongSortMgr::SongFilter& GetFilter() const;
    Symbol GetFilteredPartSym() const;

    int mNumSongs; // 0x7c
    SongSortMgr::SongFilter mFilter; // 0x80
    Symbol mPartDifficultySym; // 0x94
};