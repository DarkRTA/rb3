#pragma once
#include "obj/Object.h"
#include "meta/StoreOffer.h"

class StoreTitleContentState;

class StoreVersionHeader {
public:

};

class StoreOfferTable {
public:
    ~StoreOfferTable();
    bool Load(const char*);
    int OfferIndex(const StorePackedOfferBase*) const;

    int mNumOffers; // 0x0
    char* mBuffer; // 0x4
    StorePackedOffer** mOffers; // 0x8
    StoreOfferState* mBufferNewRelease; // 0xc
    unsigned short mNumNewReleases; // 0x10
    unsigned short* mNewReleases; // 0x14
};

class StoreRbnOfferTable {
public:
    ~StoreRbnOfferTable();
    bool Load(const char*);
    int OfferIndex(const StorePackedOfferBase*) const;

    int mNumOffers; // 0x0
    char* mBuffer; // 0x4
    StorePackedRBNOffer** mOffers; // 0x8
    StoreOfferState* mBufferNewRelease; // 0xc
    unsigned short mNumNewReleases; // 0x10
    unsigned short* mNewReleases; // 0x14
};

class StoreSingleStringTable {
public:
    ~StoreSingleStringTable(){
        if(mBuffer) _MemFree(mBuffer);
    }
    bool LoadFile(const char*);
    const char* GetString(int idx) const {
        if(idx < 0 || idx >= mNumStrings) return "STRING INDEX OUT OF BOUNDS";
        else return mStrings[idx];
    }

    int mNumStrings; // 0x0
    char* mBuffer; // 0x4
    char** mStrings; // 0x8
};

class StoreStringTable {
public:
    ~StoreStringTable(){}
    bool Load(const char*);
    bool IsValid(int);

    StoreSingleStringTable mNonLocalized; // 0x0
    StoreSingleStringTable mLocalized; // 0xc
};

class StorePackedPage {
public:
    void EndianFix();
    Symbol DefaultSort() const;

    int unk4;
    unsigned char unk5;
    unsigned short unk6;
};

class StorePage {
public:
    StorePage() : mPageNumber(0), mPage(0), unk8(0) {}
    void LoadFromBuffer(char*, unsigned short);

    int mPageNumber; // 0x0
    StorePackedPage* mPage; // 0x4
    int unk8;
};

class StorePageTable {
public:
    int mNumOffsets; // 0x0
    int mNumPages; // 0x4
    char* mBuffer; // 0x8
    StorePage* mPages; // 0xc
    std::map<unsigned short, StorePage*> mPageLookup; // 0x10
};

class StoreMetadataManager : public Hmx::Object {
public:
    StoreMetadataManager() : mFlags(0), mLoadingState(0), mBasePath(),
        mVersion(0), mStringTable(0), mSongTable(0), mOfferTable(0), mRbnOfferTable(0), mPageTable(0),
        mCurrentPage(0), unk50(0), unk54(0) {}
    ~StoreMetadataManager(){}
    virtual DataNode Handle(DataArray*, bool);

    StoreOfferState* GetOfferStatus(const class StorePackedOfferBase*);
    void Init();
    void UpdateOfferOwnership();
    void Load(const char*);
    void SetLoadingState(int);
    void Unload();
    const char* GetString(int idx) const {
        StoreStringTable* table = mStringTable;
        if(idx & 0x8000) return table->mLocalized.GetString((idx & 0x7FFF) - 1);
        else return table->mNonLocalized.GetString(idx - 1);
    }

    static std::vector<int> mSetlistOffers;

    unsigned int mFlags; // 0x1c
    int mLoadingState; // 0x20 - loading state
    int mContentSize; // 0x24
    String mBasePath; // 0x28
    StoreVersionHeader* mVersion; // 0x34
    StoreStringTable* mStringTable; // 0x38
    StoreSongTable* mSongTable; // 0x3c
    StoreOfferTable* mOfferTable; // 0x40
    StoreRbnOfferTable* mRbnOfferTable; // 0x44
    StorePageTable* mPageTable; // 0x48
    StorePage* mCurrentPage; // 0x4c
    int unk50; // ptr to StoreMarqueeTable
    int unk54;
    std::map<unsigned long long, StoreTitleContentState*> unk58;
    int unk70;
    int unk74;
    // this here is a struct - StorePage
    int unk78;
    int unk7c; // 0x7c - some other buffer
    int unk80; // 0x80 - yet another buffer
    // end struct
    int mErrorMsg; // 0x84
    int unk88;
    int unk8c;
    unsigned short unk90;
    int unk94;
    std::list<std::pair<unsigned long long, unsigned short> > unk98;
    int unka0;
};

extern StoreMetadataManager TheStoreMetadata;