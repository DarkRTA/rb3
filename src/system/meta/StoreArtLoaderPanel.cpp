#include "meta/StoreArtLoaderPanel.h"
#include "os/CommerceMgr_Wii.h"
#include "utl/BufStream.h"
#include "utl/NetCacheMgr.h"

StoreArtLoaderPanel::StoreArtLoaderPanel(){

}

StoreArtLoaderPanel::~StoreArtLoaderPanel(){
    ClearArt();
}

void StoreArtLoaderPanel::Poll(){
    UIPanel::Poll();
    for(std::vector<ArtEntry>::iterator it = mArtList.begin(); it != mArtList.end(); ++it){
        if(it->unkc){
            if(it->unkc->IsLoaded()){
                int size = it->unkc->GetSize();
                void* pBuffer = it->unkc->GetBuffer();
                MILO_ASSERT(pBuffer, 0x31);
                it->unk10 = new RndBitmap();
                BufStream bs(pBuffer, size, true);
                if(it->unk10->LoadSafely(bs, 256, 256)){
                    it->unk10->SetMip(0);
                }
                TheNetCacheMgr->DeleteNetCacheLoader(it->unkc);
                it->unkc = 0;
            }
            else {
                if(it->unkc->HasFailed()){
                    MILO_WARN("StoreArtLoaderPanel: Failed to load %s\n", it->unk0.c_str());
                    TheNetCacheMgr->DeleteNetCacheLoader(it->unkc);
                    it->unkc = 0;
                }
            }
        }
    }
}

void StoreArtLoaderPanel::Load(){
    TheWiiCommerceMgr.InitCommerce(0);
    UIPanel::Load();
}

void StoreArtLoaderPanel::Unload(){
    ClearArt();
    TheWiiCommerceMgr.DestroyCommerce();
    UIPanel::Unload();
}

void StoreArtLoaderPanel::EnsureArtLoader(const String& str){
    std::vector<ArtEntry>::iterator it = mArtList.begin();
    for(; it != mArtList.end(); ++it){
        if(it->unk0 == str) return;
    }
    ArtEntry entry;
    entry.unk0 = str;
    entry.unkc = TheNetCacheMgr->AddNetCacheLoader(str.c_str(), (NetLoaderPos)1);
    entry.unk10 = 0;
    mArtList.push_back(entry);
}

RndBitmap* StoreArtLoaderPanel::GetBmp(const String& str){
    if(str.empty()) return nullptr;
    else {
        for(std::vector<ArtEntry>::iterator it = mArtList.begin(); it != mArtList.end(); ++it){
            if(it->unk0 == str) return it->unk10;
        }
    }
    MILO_WARN("%s isn't in mArtList\n", str.c_str());
    return nullptr;
}

bool StoreArtLoaderPanel::IsAllArtLoadedOrFailed(){
    for(std::vector<ArtEntry>::iterator it = mArtList.begin(); it != mArtList.end(); ++it){
        if(it->unkc) return false;
    }
    return true;
}

void StoreArtLoaderPanel::ClearArt(){
    for(std::vector<ArtEntry>::iterator it = mArtList.begin(); it != mArtList.end(); ++it){
        TheNetCacheMgr->DeleteNetCacheLoader(it->unkc);
        RELEASE(it->unk10);
    }
    mArtList.clear();
}

BEGIN_HANDLERS(StoreArtLoaderPanel)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0xC2)
END_HANDLERS