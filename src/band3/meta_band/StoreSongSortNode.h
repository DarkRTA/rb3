#pragma once
#include "SongSortNode.h"
#include "meta/StoreOffer.h"

class StoreSongSortNode : public SongSortNode {
public:
    StoreSongSortNode(SongSortCmp *, StoreOffer *);
    virtual ~StoreSongSortNode();
    virtual DataNode Handle(DataArray *, bool);
    virtual SongNodeType GetType() const;
    virtual Symbol GetToken() const;
    virtual bool IsEnabled() const;
    virtual const char *GetAlbumArtPath();
    virtual int GetTotalMs() const;
    virtual const char *GetTitle() const;
    virtual const char *GetArtist() const;
    virtual bool GetIsCover() const;
    virtual const char *GetAlbum() const;
    virtual int GetTier(Symbol) const;

    int unk34;
    int unk38;
};