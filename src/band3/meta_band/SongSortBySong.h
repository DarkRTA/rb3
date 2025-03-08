#pragma once
#include "meta_band/SongSort.h"
#include "meta_band/SongSortNode.h"
#include "utl/Symbols.h"

class SongCmp : public SongSortCmp {
public:
    SongCmp(const char *name, Symbol header) : mName(name), mHeaderSym(header) {}
    virtual ~SongCmp() {}
    virtual int Compare(SongSortCmp const *, SongNodeType) const;
    virtual const SongCmp *GetSongCmp() const { return this; }

    const char *mName; // 0x4
    Symbol mHeaderSym; // 0x8
};

class SongSortBySong : public SongSort {
    SongSortBySong() { mShortName = by_song; }
    virtual ~SongSortBySong() {}
    virtual void Init();
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const;
    virtual OwnedSongSortNode *NewSongNode(SongRecord *) const;
    virtual StoreSongSortNode *NewSongNode(class StoreOffer *) const;
};