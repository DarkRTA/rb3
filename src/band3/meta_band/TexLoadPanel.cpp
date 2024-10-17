#include "meta_band/TexLoadPanel.h"
#include "decomp.h"
#include "meta_band/BandSongMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "rndobj/Mesh.h"
#include "ui/UIPanel.h"
#include "utl/Loader.h"
#include "utl/STLHelpers.h"
#include "utl/Symbol.h"
#include "utl/Symbols2.h"
#include "utl/Symbols4.h"

DynamicTex::DynamicTex(const char* c1, const char* c2, bool b1, bool b2) : mTex(Hmx::Object::New<RndTex>()), mMatName(c2), mMat(0), mLoader(0), unk1c(b2) {
    if(c1 != gNullStr){
        mLoader = dynamic_cast<FileLoader*>(TheLoadMgr.AddLoader(FilePath(c1), kLoadFront));
        MILO_ASSERT(mLoader, 0x1B);
    }
    if(b1){
        mMat = Hmx::Object::New<RndMat>();
        if(unk1c) mMat->SetZMode(kNormal);
        else mMat->SetZMode(kDisable);
        mMat->SetBlend(kSrcAlpha);
    }
}

DECOMP_FORCEACTIVE(DynamicTex, "mMat")

DynamicTex::~DynamicTex(){
    delete mMat;
    delete mLoader;
    delete mTex;
}

bool operator==(const DynamicTex* tex, const String& str){ return tex->mMatName == str; }

void DLCTex::StartLoading(){
    MILO_ASSERT(mState == kMounting, 0x46);
    const char* path = TheSongMgr->GetAlbumArtPath(unk20);
    MILO_ASSERT(path != gNullStr, 0x48);
    mLoader = dynamic_cast<FileLoader*>(TheLoadMgr.AddLoader(FilePath(path), kLoadFront));
    MILO_ASSERT(mLoader, 0x4A);
    mState = 2;
}

TexLoadPanel::TexLoadPanel() : unk3c(0), mCurrentFinalizingTexture(-1) {

}

void TexLoadPanel::Load(){
    unk3c = 1;
    UIPanel::Load();
    if(RegisterForContent()){
        TheContentMgr->RegisterCallback(this, false);
    }
}

bool TexLoadPanel::IsLoaded() const {
    if(unk3c != 3) return false;
    else return UIPanel::IsLoaded();
}

void TexLoadPanel::FinishLoad(){ UIPanel::FinishLoad(); }

void TexLoadPanel::PollForLoading(){
    UIPanel::PollForLoading();
    switch(unk3c){
        case 1:
            if(TexturesLoaded()){
                mCurrentFinalizingTexture = 0;
                unk3c = 2;
            }
            break;
        case 2:
            FinalizeTexturesChunk();
            if(mCurrentFinalizingTexture >= mTexs.size()) unk3c = 3;
            break;
        default: break;
    }
}

void TexLoadPanel::Poll(){
    UIPanel::Poll();
    DLCTex* dlc = NextDLCTex();
    if(dlc){
        MILO_ASSERT(dlc->mState != DLCTex::kLoaded, 0x93);
        switch(dlc->mState){
            case 0:
                const char* name = TheSongMgr->ContentName(dlc->unk20, true);
                dlc->mState = 1;
                // WiiContentMgr stuff
                break;
            case 2:
                MILO_ASSERT(dlc->mLoader, 0xA4);
                if(dlc->mLoader->IsLoaded()){
                    MILO_ASSERT(dlc->mTex, 0xA7);
                    MILO_ASSERT(dlc->mMat, 0xA8);
                    dlc->mTex->SetBitmap(dlc->mLoader);
                    dlc->mLoader = 0;
                    dlc->mMat->SetDiffuseTex(dlc->mTex);
                    dlc->mState = 3;
                }
                break;
            default: break;
        }
    }
}

void TexLoadPanel::Unload(){
    if(RegisterForContent()){
        TheContentMgr->UnregisterCallback(this, false);
    }
    DeleteAll(mTexs);
    unk3c = 0;
    mCurrentFinalizingTexture = -1;
    UIPanel::Unload();
}

void TexLoadPanel::ContentMounted(const char* c1, const char* c2){
    DLCTex* dlc = NextDLCTex();
    if(dlc){
        String name(TheSongMgr->ContentName(dlc->unk20, true));
        if(name == c1) dlc->StartLoading();
        else MILO_WARN("Someone else is mounting %s", c1);
    }
}

void TexLoadPanel::ContentFailed(const char* c1){
    DLCTex* dlc = NextDLCTex();
    if(dlc){
        String name(TheSongMgr->ContentName(dlc->unk20, true));
        if(name == c1){
            dlc->mMat->SetDiffuseTex(dlc->unk28);
            dlc->mState = 3;
        }
        else MILO_WARN("Someone else is mounting %s", c1);
    }
}

DLCTex* TexLoadPanel::NextDLCTex(){
    for(std::vector<DynamicTex*>::iterator it = mTexs.begin(); it != mTexs.end(); ++it){
        DLCTex* dlc = dynamic_cast<DLCTex*>(*it);
        if(dlc && dlc->mState != 3) return dlc;
    }
    return nullptr;
}

bool TexLoadPanel::TexturesLoaded() const {
    for(std::vector<DynamicTex*>::const_iterator it = mTexs.begin(); it != mTexs.end(); ++it){
        DynamicTex* tex = *it;
        if(tex->mLoader && !tex->mLoader->IsLoaded()) return false;
    }
    return true;
}

bool TexLoadPanel::RegisterForContent() const {
    const DataArray* tdef = TypeDef();
    if(tdef){
        DataArray* regArr = tdef->FindArray(register_for_content, false);
        if(regArr) return regArr->Int(1);
    }
    return false;
}

void TexLoadPanel::FinalizeTexturesChunk(){
    int numTextures = mTexs.size();
    int count = numTextures - mCurrentFinalizingTexture;
    if(count > 0x32) count = 0x32;
    for(int i = 0; i < count; i++){
        MILO_ASSERT(mCurrentFinalizingTexture < numTextures, 0x10F);
        DynamicTex* t = mTexs[mCurrentFinalizingTexture];
        if(t->mLoader){
            MILO_ASSERT(t->mLoader->IsLoaded(), 0x114);
            MILO_ASSERT(t->mTex, 0x115);
            t->mTex->SetBitmap(t->mLoader);
            t->mLoader = 0;
            if(t->mMat){
                t->mMat->SetDiffuseTex(t->mTex);
            }
            else {
                RndMat* found = mDir->Find<RndMat>(t->mMatName.c_str(), false);
                if(found) found->SetDiffuseTex(t->mTex);
                else MILO_WARN("Could not find %s", t->mMatName);
            }
        }
        mCurrentFinalizingTexture++;
    }
}

DECOMP_FORCEACTIVE(TexLoadPanel, "RegisterForContent()")

DynamicTex* TexLoadPanel::AddTex(const char* c1, const char* c2, bool b1, bool b2){
    DynamicTex* tex = new DynamicTex(c1, c2, b1, b2);
    mTexs.push_back(tex);
    return tex;
}

BEGIN_HANDLERS(TexLoadPanel)
    HANDLE_ACTION(add_tex, AddTex(_msg->Str(2), _msg->Str(3), false, false))
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x139)
END_HANDLERS