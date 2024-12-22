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

class StoreMetadataManager : public Hmx::Object {
public:
    StoreMetadataManager() : mFlags(0), mLoadingState(0), mBasePath(),
        mVersion(0), mStringTable(0), unk3c(0), mOfferTable(0), mRbnOfferTable(0), unk48(0),
        unk4c(0), unk50(0), unk54(0) {}
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
    int unk3c; // ptr to StoreSongTable
    StoreOfferTable* mOfferTable; // 0x40
    StoreRbnOfferTable* mRbnOfferTable; // 0x44
    int unk48; // ptr to StorePageTable
    int unk4c; // ptr to StorePage
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