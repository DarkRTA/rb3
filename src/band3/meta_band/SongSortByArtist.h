#pragma once
#include "SongSortNode.h"
#include "meta_band/SongSort.h"
#include "utl/Symbols2.h"

class ArtistCmp : public SongSortCmp {
public:
    ArtistCmp(
        Symbol shortcut,
        const char *artist,
        bool cover,
        const char *album,
        int track,
        const char *song
    )
        : mShortcut(shortcut), mArtist(artist), mCover(cover), mAlbum(album),
          mTrackNum(track), mSongName(song) {}
    virtual ~ArtistCmp() {}
    virtual int Compare(SongSortCmp const *, SongNodeType) const;
    virtual bool HasSubheader() const;
    virtual void Finish() { mTrackNum = -1; }
    virtual const ArtistCmp *GetArtistCmp() const { return this; }

    Symbol mShortcut; // 0x4
    const char *mArtist; // 0x8
    bool mCover; // 0xc
    const char *mAlbum; // 0x10
    int mTrackNum; // 0x14
    const char *mSongName; // 0x18
};

class SongSortByArtist : public SongSort {
    SongSortByArtist() { mShortName = by_artist; }
    virtual ~SongSortByArtist() {}
    virtual void Init();
    virtual void ConfirmSubheaders(HeaderSortNode *);
    virtual ShortcutNode *NewShortcutNode(SongSortNode *) const;
    virtual HeaderSortNode *NewHeaderNode(SongSortNode *) const;
    virtual SubheaderSortNode *NewSubheaderNode(SongSortNode *) const;
    virtual OwnedSongSortNode *NewSongNode(SongRecord *) const;
    virtual StoreSongSortNode *NewSongNode(class StoreOffer *) const;
};