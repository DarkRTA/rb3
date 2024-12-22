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
    char* mBufferNewRelease; // 0xc
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
    char* mBufferNewRelease; // 0xc
    unsigned short mNumNewReleases; // 0x10
    unsigned short* mNewReleases; // 0x14
};

class StoreMetadataManager : public Hmx::Object {
public:
    StoreMetadataManager() : mFlags(0), unk20(0), unk28(),
        unk34(0), unk38(0), unk3c(0), mOfferTable(0), mRbnOfferTable(0), unk48(0),
        unk4c(0), unk50(0), unk54(0) {}
    ~StoreMetadataManager(){}
    virtual DataNode Handle(DataArray*, bool);

    StoreOfferState* GetOfferStatus(const class StorePackedOfferBase*); // change ret type! to StoreOfferState
    void Init();
    void UpdateOfferOwnership();

    static std::vector<int> mSetlistOffers;

    unsigned int mFlags; // 0x1c
    int unk20; // 0x20 - loading state
    int unk24;
    String unk28; // 0x28
    int unk34; // some buffer
    int unk38;
    int unk3c; // ptr to StoreSongTable
    StoreOfferTable* mOfferTable; // 0x40
    StoreRbnOfferTable* mRbnOfferTable; // 0x44
    int unk48; // ptr to StorePageTable
    int unk4c;
    int unk50; // ptr to StoreMarqueeTable
    int unk54;
    std::map<unsigned long long, StoreTitleContentState*> unk58;
    int unk70;
    int unk74;
    int unk78;
    int unk7c;
    int unk80;
    int unk84; // 0x84 - error msg
    int unk88;
    int unk8c;
    int unk90;
    int unk94;
    std::list<std::pair<unsigned long long, unsigned short> > unk98;
};

extern StoreMetadataManager TheStoreMetadata;