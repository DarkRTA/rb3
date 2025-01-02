#pragma once
#include "obj/Object.h"
#include "meta/SongMgr.h"
#include "ui/UILabel.h"

enum StoreOfferType {
    kStoreOfferSong = 0,
    kStoreOfferAlbum = 1,
    kStoreOfferPack = 2
};

class StorePackedSong {
public:
    void EndianFix();
    const char* GetShortName() const;
    const char* GetName() const;
    const char* GetArtist() const;
    const char* GetDataTitle() const;
    const char* GetUpgradeDataTitle() const;

    unsigned int mSongID; // 0x0
    unsigned short unk4;
    char unk6;
    char unk7;
    char unk8;
    char unk9;
    unsigned short unka;
    char unkc;
    char unkd;
    char unke;
    char unkf;
    unsigned short unk10; // 0x10
    unsigned short mNameIndex; // 0x12
    unsigned short mArtistIndex; // 0x14
    int unk18;
};

class StoreSongTable {
public:
    ~StoreSongTable();
    bool Load(const char*);

    int mNumSongs; // 0x0
    char* mBuffer; // 0x4
    StorePackedSong* mSongs; // 0x8
};

class StorePackedRanks {
public:
    unsigned int mBand : 10;
    unsigned int mVocals : 10;
    unsigned int mGuitar : 10;
    unsigned int mBass : 10;
    unsigned int mDrums : 10;
    unsigned int mKeys : 10;
    unsigned int mRealGuitar : 10;
    unsigned int mRealBass : 10;
    unsigned int mRealKeys : 10;
};

class StoreOfferState {
public:
    void UpdateFlags(class StorePackedOfferBase*, unsigned char, unsigned char);

    unsigned short mPrice; // 0x0
    unsigned short unk2;
    unsigned char mFlags; // 0x4
    int unk8;
};

#pragma push
#pragma pack(1)
class StorePackedOfferBase {
public:
    const char* GetName() const;
    StoreOfferType OfferType() const { return (StoreOfferType)mOfferType; }
    int Genre() const { return mGenre; }
    const char* GetArtist() const;
    const char* GetAlbumName() const;
    String GetOfferId() const;
    String GetUpgradeId() const;
    bool IsVariousArtist() const;

    // 0x0
    unsigned char mIsRBN : 1;
    unsigned char mOfferType : 2;
    unsigned char mRating : 3;
    unsigned char mNewRelease : 1;
    // 0x1
    unsigned char mGenre : 5;
    unsigned char mCover : 1;
    unsigned char mVocalParts : 2;

    char mId[16]; // 0x2
    char mUpgradeId[16]; // 0x12
    unsigned short mNameIndex; // 0x22
    unsigned short mArtistIndex; // 0x24
    unsigned char mYearReleased; // 0x26
    unsigned short mArtIndex; // 0x27
    unsigned short mAlbumIndex; // 0x29
    StorePackedRanks mRanks; // 0x2b
    unsigned short mAlbumLink; // 0x37
    unsigned short mPackLink; // 0x39
    float mReview; // 0x3b
    unsigned char unk3f;
    unsigned char unk40;
    unsigned char unk41;
    unsigned char mNumSongs; // 0x42
};

class StorePackedOffer : public StorePackedOfferBase {
public:
    const char* GetArtPath() const;
    const char* GetPreviewPath() const;
    void EndianFix();
    StorePackedSong* GetPackedSong(int) const;

    unsigned short mSongs[1]; // 0x43
};

class StorePackedRBNOffer : public StorePackedOfferBase {
public:
    const char* GetArtPath() const;
    const char* GetPreviewPath() const;
    void EndianFix();
    StorePackedSong* GetPackedSong(int) const;

    int SubGenre() const { return mSubGenre; }
    int Language() const { return mLanguage; }
    const char* LabelStr() const;
    const char* AuthorStr() const;

    unsigned char mSubGenre : 7; // 0x43
    unsigned char mLanguage : 3; // 0x44
    unsigned char unk44 : 5;
    unsigned short mAuthorIndex; // 0x45
    unsigned short mLabelIndex; // 0x47
    unsigned short mSongs[1]; // 0x49
};
#pragma pop

class StorePurchaseable : public Hmx::Object {
public:
    StorePurchaseable();
    virtual ~StorePurchaseable(){}

    bool Exists() const;
    const char* CostStr() const;
    bool IsDownloaded() const { return mOfferState->mFlags & 2; }
    bool IsPartiallyDownloaded() const { return mOfferState->mFlags & 4; }
    bool IsPartiallyPurchased() const { return mOfferState->mFlags & 8; }
    bool IsPurchased() const;
    bool IsAvailable() const {
        return mOfferState && mOfferState->mFlags & 0x40;
    }
    void GetContentIndexes(std::vector<unsigned short>&, bool) const;
    unsigned long long GetTitleId() const;
    unsigned long long GetUpgradeTitleId() const;

    StorePackedSong* GetPackedSong(int idx) const {
        if(mPackedData->mIsRBN){
            return mPackedRbnOffer->GetPackedSong(idx);
        }
        else {
            return mPackedOffer->GetPackedSong(idx);
        }
    }

    union {
        const StorePackedOfferBase* mPackedData;
        const StorePackedOffer* mPackedOffer;
        const StorePackedRBNOffer* mPackedRbnOffer;
    }; // 0x1c
    StoreOfferState* mOfferState; // 0x20
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
    Symbol VocalPartsSym() const;
    const char* AlbumName() const;
    int NumSongs() const;
    bool HasArtist() const;
    unsigned int GetSingleSongID() const;
    bool HasSong(const StoreOffer*) const;
    bool HasSolo() const;

    bool IsRbn() const {
        return mPackedData->mIsRBN;
    }

    StorePurchaseable mAlbum; // 0x24
    StorePurchaseable mPack; // 0x48
    String unk6c; // 0x6c - release date str
    SongMgr* mSongMgr; // 0x78
};

bool StoreOfferSort(const StoreOffer* o1, const StoreOffer* o2);