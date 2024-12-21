#pragma once
#include "obj/Object.h"
#include "meta/SongMgr.h"
#include "ui/UILabel.h"

enum StoreOfferType {
    kStoreOfferSong = 0,
    kStoreOfferAlbum = 1,
    kStoreOfferPack = 2
};

class StorePackedOfferBase {
public:
    const char* GetName() const;
    StoreOfferType OfferType() const { return (StoreOfferType)mOfferType; }
    int Genre() const { return mGenre; }

    // 0x0
    unsigned char mIsRBN : 1;
    unsigned char mOfferType : 2;
    unsigned char mRating : 3;
    unsigned char mNewRelease : 1;
    // 0x1
    unsigned char mGenre : 5;
    unsigned char mCover : 1;
    unsigned char mVocalParts : 2;

    int unk4;
    int unk8;
    int unkc;
    int unk10;
    int unk14;
    int unk18;
    int unk1c;
    int unk20;
    char unk24;
    char unk25;
    unsigned char mYearReleased; // 0x26
};

class StorePackedOffer : public StorePackedOfferBase {
public:
};

class StorePackedRBNOffer : public StorePackedOfferBase {
public:
};

class StorePurchaseable : public Hmx::Object {
public:
    StorePurchaseable();
    virtual ~StorePurchaseable(){}

    bool Exists() const;
    const char* CostStr() const;
    bool IsDownloaded() const;
    bool IsPartiallyDownloaded() const;
    bool IsPartiallyPurchased() const;

    union {
        const StorePackedOfferBase* mPackedData;
        const StorePackedOffer* mPackedOffer;
        const StorePackedRBNOffer* mPackedRbnOffer;
    } mPacked; // 0x1c
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
    Symbol ShortName() const;
    const char* OfferName() const;
    const char* Description() const;
    DataArray* DescriptionData(UILabel*) const;
    int YearReleased() const;
    Symbol SubGenre() const;
    bool InLibrary() const;
    bool IsAvailable() const;
    bool IsPurchased() const;
    bool IsTest() const;
    Symbol PackFirstLetter() const;
    const char* ReleaseDateStr() const;
    float Review() const;
    const char* Artist() const;
    float PartRank(Symbol) const;
    Symbol Label() const;
    Symbol Author() const;
    Symbol Language() const;
    const char* PreviewAudio() const;
    const char* PreviewArt() const;
    Symbol RatingSym() const;
    bool HasPreviewArt() const;
    Symbol FirstCharArtist(bool) const;
    Symbol FirstCharName(bool) const;
    const char* AlbumLink() const;
    const char* PackLink() const;

    bool IsRbn() const {
        return mPacked.mPackedData->mIsRBN;
    }

    StorePurchaseable mAlbum; // 0x24
    StorePurchaseable mPack; // 0x48
    String unk6c; // 0x6c
    SongMgr* unk74; // 0x74
};