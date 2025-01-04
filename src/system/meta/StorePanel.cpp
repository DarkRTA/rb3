#include "meta/StorePanel.h"
#include "meta/StorePackedMetadata.h"
#include "meta/StoreOffer.h"
#include "os/ContentMgr.h"
#include "os/CommerceMgr_Wii.h"
#include "os/PlatformMgr.h"
#include "utl/NetCacheMgr.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

bool gStoreAllowBandShotForceShowing = true;

StorePanel::StorePanel() : mLoadOK(0), mShowTestOffers(1), mPendingArtLoader(0), mAlbumTex(Hmx::Object::New<RndTex>()), mPendingArtCallback(0), mStorePreviewMgr(0), mEnum(0), unk70(0), unk71(0),
    mPurchaser(0), mSource(gNullStr), mBackupSource(gNullStr), mSessionStatus(kSessionNone), mCurrentOffer(0), mCurrentOfferUpgrade(0), unk89(0), mStoreMode(0) {

}

StorePanel::~StorePanel(){
    DeleteAll(unk38);
    DeleteAll(unk40);
    delete mAlbumTex;
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

void StorePanel::HandleNetCacheMgrFailure(){
    StoreError err = kStoreErrorSuccess;
    NetCacheMgrFailType failTy = TheNetCacheMgr->GetFailType();
    switch(failTy){
        case kNCMFT_StoreServer:
        case kNCMFT_NoSpace:
            MILO_WARN("Failure %d in NetCacheMgr.\n", failTy);
            break;
        case kNCMFT_StorageDeviceMissing:
            err = kStoreErrorNoMetadata;
            break;
        default:
            MILO_WARN("Unknown failure %d in NetCacheMgr.\n", failTy);
            break;
    }
    if(err != kStoreErrorNoMetadata && !ThePlatformMgr.IsEthernetCableConnected()){
        err = kStoreErrorNoMetadata;
    }
    if(err != kStoreErrorSuccess) ExitError(err);
}

DECOMP_FORCEACTIVE(StorePanel, "( 0) <= (failType) && (failType) < ( kNCMFT_Max)", "Unknown failure %d in a net cache loader!\n")

bool StorePanel::IsLoaded() const {
    return UIPanel::IsLoaded() && TheContentMgr->RefreshDone() &&
        (mSessionStatus == kSessionCreated || !mLoadOK);
}

void StorePanel::PollForLoading(){
    UIPanel::PollForLoading();
    if(mLoadOK && mSessionStatus == kSessionNone && TheNetCacheMgr->IsReady()){
        if(!TheWiiCommerceMgr.InitCommerce(this)){
            ExitError((StoreError)100);
        }
        else mSessionStatus = kSessionCreating;
    }
    else if(TheNetCacheMgr->unk_0x20) HandleNetCacheMgrFailure();
}

void StorePanel::LoadMetadata(){
    if(mLoadOK && mSessionStatus == kSessionCreated){
        TheStoreMetadata.Load("store_test/");
    }
}

bool StorePanel::IsMetadataLoaded(){
    if(TheStoreMetadata.LoadingFailed()){
        ExitError(TheStoreMetadata.LoadError());
        return false;
    }
    else return 1;
}

void StorePanel::Enter(){
    UIPanel::Enter();
    gStoreAllowBandShotForceShowing = false;
    SetShowing(mLoadOK);
    unk70 = false;
}

void StorePanel::Poll(){

}

void StorePanel::Exit(){
    gStoreAllowBandShotForceShowing = true;
    UIPanel::Exit();
}

bool StorePanel::Exiting() const {
    
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

bool StorePanel::IsEnumerating() const {
    return mEnum && mEnum->IsEnumerating();
}

bool StorePanel::InCheckout() const {
    return mPurchaser;
}

void StorePanel::LoadArt(const char* cc, UIPanel* panel){
    String str(cc);
    for(std::list<StorePanel*>::iterator it = unk54.begin(); it != unk54.end(); ++it){

    }
    mPendingArtCallback = panel;
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

void StorePanel::PopulateOffers(DataArray*, bool){
    DeleteAll(unk38);
    DeleteAll(unk40);
    std::sort(unk38.begin(), unk38.end(), StoreOfferSort);
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