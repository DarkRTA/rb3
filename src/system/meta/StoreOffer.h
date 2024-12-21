#pragma once
#include "obj/Object.h"
#include "meta/SongMgr.h"

class StorePackedOfferBase {
public:
    // 0x0
    unsigned char sometopthing : 1;
    unsigned char mOfferType : 2;
    unsigned char mRating : 3;
    unsigned char mNewRelease : 1;
    unsigned char asdf : 1;
    // 0x1
    unsigned char mGenre : 5;
    unsigned char mCover : 1;
    unsigned char mVocalParts : 2;
};

class StorePurchaseable : public Hmx::Object {
public:
    StorePurchaseable();
    virtual ~StorePurchaseable(){}

    bool Exists() const;
    const char* CostStr() const;

    const StorePackedOfferBase* unk1c; // 0x1c - union between PackedOffer and RBNPackedOffer?
    int unk20; // 0x20 - ptr to some struct
};

class StoreOffer : public StorePurchaseable {
public:
    StoreOffer(const StorePackedOfferBase*, SongMgr*, bool);
    ~StoreOffer();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool IsCompletelyUnavailable() const;

    Symbol OfferType() const;
    bool IsNewRelease() const;
    bool IsCover() const;
    int Rating() const;
    int VocalParts() const;
    Symbol Genre() const;
    bool HasPreviewAudio() const;
    bool HasGenre() const;
    bool HasVocalParts() const;
    Symbol LengthSym() const;
    Symbol Decade() const;

    StorePurchaseable mAlbum; // 0x24
    StorePurchaseable mPack; // 0x48
    String unk6c; // 0x6c
    SongMgr* unk74; // 0x74
};