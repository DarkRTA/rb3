#include "meta/StorePackedMetadata.h"
#include "meta/StoreOffer.h"

StoreMetadataManager TheStoreMetadata;
std::vector<int> StoreMetadataManager::mSetlistOffers;
bool gDebugMakeAllSongsAvailable;
bool gDebugDontRelyOnCommerceServer;

bool StoreLoadPackedFile(const char*, bool, int, bool, bool, char**, char**, char**, int*){

}

bool StoreStringTable::Load(const char* cc){
    char buf[256];
    sprintf(buf, "%sstrings", cc);
    bool nonloc = mNonLocalized.LoadFile(buf);
    sprintf(buf, "%sstrings_%s", cc, SystemLanguage().mStr);
    return nonloc && mLocalized.LoadFile(buf);
}

bool StoreStringTable::IsValid(int i){
    if(i & 0x8000U){
        if(mLocalized.mNumStrings <= (i & 0x7FFFU)) return false;
        else return true;
    }
    else return i >= 0 && i < mNonLocalized.mNumStrings;
}

String StorePackedOfferBase::GetOfferId() const {
    String ret;
    ret.reserve(0x11);
    memcpy((void*)ret.c_str(), mId, 16);
    char* ptr = (char*)ret.c_str();
    ptr[16] = 0;
    return ret;
}

String StorePackedOfferBase::GetUpgradeId() const {
    String ret;
    ret.reserve(0x11);
    memcpy((void*)ret.c_str(), mUpgradeId, 16);
    char* ptr = (char*)ret.c_str();
    ptr[16] = 0;
    return ret;
}

const char* StorePackedOfferBase::GetName() const {
    return TheStoreMetadata.GetString(mNameIndex);
}

StoreOfferTable::~StoreOfferTable(){
    if(mBuffer){
        _MemFree(mBuffer);
        mBuffer = 0;
    }
    delete [] mBufferNewRelease;
    mBufferNewRelease = 0;
}

bool StoreOfferTable::Load(const char* cc){
    char buf[256];
    sprintf(buf, "%soffers", cc);

    char* loc12c;
    char* loc130;
    bool ret = StoreLoadPackedFile(buf, true, 0x40000, true, true, &mBuffer, &loc12c, &loc130, &mNumOffers);
    if(!ret) return ret;
    else {
        int diff = loc130 - loc12c;
        int u4 = diff / 0x45ul;
        if(u4 < mNumOffers){
            MILO_LOG("There are %d bytes left in offers file, at %d bytes per offer is %d offers, but the file says there are %d offers.\n", 
                diff, 0x45ul, u4, mNumOffers);
        }
        (char**)mOffers = &loc12c;
        mBufferNewRelease = new StoreOfferState[mNumOffers];
        memset(mBufferNewRelease, 0, mNumOffers);
        for(int i = 0; i < mNumOffers; i++){
            StorePackedOffer* curOffer = mOffers[i];
            curOffer->EndianFix();
        }
        return true;
    }
}

int StoreOfferTable::OfferIndex(const StorePackedOfferBase* base) const {
    for(int i = 0; i < mNumOffers; i++){
        if(base == mOffers[i]) return i;
    }
    return -1;
}

StoreRbnOfferTable::~StoreRbnOfferTable(){
    if(mBuffer){
        _MemFree(mBuffer);
        mBuffer = 0;
    }
    delete [] mBufferNewRelease;
    mBufferNewRelease = 0;
}

bool StoreRbnOfferTable::Load(const char* cc){

}

void StoreMetadataManager::Init(){
    SetName("store", ObjectDir::sMainDir);
    mLoadingState = 0;
    mContentSize = 0;
    mErrorMsg = 0;
    if(SystemConfig("store", "local_metadata")->Int(1)){
        gDebugMakeAllSongsAvailable = true;
        gDebugDontRelyOnCommerceServer = true;
        mFlags |= 1;
    }
}

void StoreOfferState::UpdateFlags(StorePackedOfferBase* base, unsigned char c1, unsigned char c2){
    mFlags &= 0xC0;
    if(c1 & 2) mFlags |= 1;
    if(c1 & 1) mFlags |= 2;
    if(c1 & 8) mFlags |= 0x20;
    if(c1 & 0x10) mFlags |= 0x10;
    if(c2 & 2) mFlags |= 8;
}

void StoreMetadataManager::UpdateOfferOwnership(){
    for(int i = 0; i < mOfferTable->mNumOffers; i++){

    }
}

void StoreMetadataManager::Load(const char* cc){
    if(!(mFlags & 0xC)){
        mBasePath = cc;
        mErrorMsg = 0;
        SetLoadingState(1);
        mFlags |= 4;
    }
}

void StoreMetadataManager::Unload(){
    RELEASE(mStringTable);
    RELEASE(mOfferTable);
    RELEASE(mRbnOfferTable);
}

StoreOfferState* StoreMetadataManager::GetOfferStatus(const StorePackedOfferBase* base){
    int idx = mOfferTable->OfferIndex(base);
    if(idx >= 0){
        return &mOfferTable->mBufferNewRelease[idx];
    }
    else {
        idx = mRbnOfferTable->OfferIndex(base);
        if(idx >= 0) return &mRbnOfferTable->mBufferNewRelease[idx];
    }
    return 0;
}
