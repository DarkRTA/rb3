#include "meta/StorePanel.h"
#include "utl/NetCacheMgr.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

StorePanel::StorePanel() : mLoadOK(0), mShowTestOffers(1), mPendingArtLoader(0), mAlbumTex(Hmx::Object::New<RndTex>()), mPendingArtCallback(0), mStorePreviewMgr(0), mEnum(0), unk70(0), unk71(0),
    mPurchaser(0), mSource(gNullStr), mBackupSource(gNullStr), mSessionStatus(kSessionNone), mCurrentOffer(0), mCurrentOfferUpgrade(0), unk89(0), mStoreMode(0) {

}

StorePanel::~StorePanel(){

}

void StorePanel::Load(){
    UIPanel::Load();
    mLoadOK = true;
    TheContentMgr->StartRefresh();
    TheNetCacheMgr->Load((NetCacheMgr::CacheSize)1);
    MILO_ASSERT(!mStorePreviewMgr, 0x84);
    mStorePreviewMgr = new StorePreviewMgr();
    mStorePreviewMgr->AddSink(this);
    MILO_ASSERT(!mPurchaser, 0x88);
    RELEASE(mEnum);
    mSessionStatus = kSessionNone;
    unk89 = false;
}

bool StorePanel::Unloading() const {
    if(GetState() != kUp && !TheNetCacheMgr->IsUnloaded()){
        return true;
    }
    else return UIPanel::Unloading();
}

StorePanel* StorePanel::Instance(){
    return ObjectDir::Main()->Find<StorePanel>("store_panel", true);
}

void StorePanel::CancelArt(){
    mPendingArtLoader = 0;
    mPendingArtCallback = 0;
}

void StorePanel::SetSource(Symbol s, bool b){
    mSource = s;
    if(b) mBackupSource = s;
    if(mSource == setlist_upsell){
        SetStoreMode(setlist);
    }
}

void StorePanel::SetSourceToBackup(){
    mSource = mBackupSource;
}

void StorePanel::SetStoreMode(Symbol s){
    if(s == dlc) mStoreMode = 0;
    else if(s == manage) mStoreMode = 1;
    else if(s == token) mStoreMode = 2;
    else if(s == setlist) mStoreMode = 3;
}

void StorePanel::EnumerateOffers(bool b){
    RELEASE(mEnum);
    int size = unk38.size();
    mEnum = new WiiEnumeration(size);
    mEnum->Start();
    Hmx::Object::HandleType(enum_start_msg);
}

void StorePanel::UpdateFromEnumProduct(StorePurchaseable* sp, const EnumProduct* ep){
    MILO_ASSERT(sp, 0x48A);
    MILO_ASSERT(ep, 0x48B);
}

bool StorePanel::ToggleTestOffers(){
    mShowTestOffers = !mShowTestOffers;
    return mShowTestOffers;
}