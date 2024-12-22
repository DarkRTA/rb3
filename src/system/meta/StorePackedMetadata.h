#pragma once
#include "obj/Object.h"
#include "meta/StoreOffer.h"

class StoreTitleContentState;

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

    int mNumStrings;
    char* mBuffer;
    char** mStrings;
};

class StoreStringTable {
public:
    ~StoreStringTable(){}

    StoreSingleStringTable mNonLocalized; // 0x0
    StoreSingleStringTable mLocalized; // 0xc
};

class StoreMetadataManager : public Hmx::Object {
public:
    StoreMetadataManager() : mFlags(0), mLoadingState(0), mBasePath(),
        unk34(0), mStringTable(0), unk3c(0), mOfferTable(0), mRbnOfferTable(0), unk48(0),
        unk4c(0), unk50(0), unk54(0) {}
    ~StoreMetadataManager(){}
    virtual DataNode Handle(DataArray*, bool);

    StoreOfferState* GetOfferStatus(const class StorePackedOfferBase*);
    void Init();
    void UpdateOfferOwnership();
    void Load(const char*);
    void SetLoadingState(int);
    void Unload();

    static std::vector<int> mSetlistOffers;

    unsigned int mFlags; // 0x1c
    int mLoadingState; // 0x20 - loading state
    int mContentSize; // 0x24
    String mBasePath; // 0x28
    int unk34; // some buffer
    StoreStringTable* mStringTable; // StoreSingleStringTable?
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