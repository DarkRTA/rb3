#include "meta_band/CharData.h"
#include "bandobj/BandCharDesc.h"
#include "meta_band/PrefabMgr.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Loader.h"
#include "utl/Locale.h"
#include "utl/MakeString.h"
#include "utl/Symbols4.h"
#include <cstddef>

CharData::CharData(){

}

CharData::~CharData(){

}

BEGIN_HANDLERS(CharData)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x20)
END_HANDLERS

const char* GetPrefabPortraitPath(PrefabChar* pPrefab){
    MILO_ASSERT(pPrefab, 0x29);
    Symbol prefabSym = pPrefab->GetPrefabName();
    static const char* strPrefix(SystemConfig(prefab_mgr)->FindStr(prefab_portrait_path_prefix));
    static const char* strSuffix(SystemConfig(prefab_mgr)->FindStr(prefab_portrait_path_suffix));
    return MakeString("%s", FilePath(strPrefix, MakeString("%s%s", prefabSym.Str(), strSuffix)).c_str());
}

PrefabChar::PrefabChar(BandCharDesc* desc) : mBandCharDesc(desc), mTexPortrait(0), mLoader(0) {
    MILO_ASSERT(mBandCharDesc, 0x3F);
    unk24 = GetPrefabPortraitPath(this);
}

PrefabChar::~PrefabChar(){
    RELEASE(mTexPortrait);
}

const char* PrefabChar::GetCharacterName() const {
    return Localize(GetPrefabName(), 0);
}

BandCharDesc* PrefabChar::GetBandCharDesc() const { return mBandCharDesc; }

RndTex* PrefabChar::GetPortraitTex() const { return mTexPortrait; }

void PrefabChar::CachePortraitTex(RndTex* tex){
    MILO_ASSERT(tex->Width() > 0 && tex->Height() > 0, 0x5A);
    tex->SaveBitmap(unk24.c_str());
}

bool PrefabChar::IsFinalized() const { return true; }
bool PrefabChar::IsCustomizable() const { return PrefabMgr::PrefabIsCustomizable(); }
Symbol PrefabChar::GetPrefabName() const { return mBandCharDesc->Name(); }

void PrefabChar::LoadPortrait(){
    if(mTexPortrait || mLoader){
        const char* loadstatus = !mLoader ? "loaded" : "loading";
        MILO_WARN("request to load portrait on %s ignored because it is already %s.\n", GetPrefabName(), loadstatus);
    }
    else {
        Loader* loader = TheLoadMgr.AddLoader(FilePath(unk24.c_str()), kLoadBack);
        mLoader = dynamic_cast<FileLoader*>(loader);
        MILO_ASSERT(mLoader, 0x88);
    }
}

void PrefabChar::PollLoadingPortrait(){
    if(mLoader){
        if(!mLoader->IsLoaded()) TheLoadMgr.Poll();
        if(mLoader->IsLoaded()){
            MILO_ASSERT(mTexPortrait == NULL, 0x9A);
            mTexPortrait = Hmx::Object::New<RndTex>();
            mTexPortrait->SetBitmap(mLoader);
            mLoader = 0;
        }
    }
}

bool PrefabChar::IsPortraitLoaded(){ return mTexPortrait; }

void PrefabChar::UnloadPortrait(){
    if(mLoader) RELEASE(mLoader);
    RELEASE(mTexPortrait);
}

RndTex* PrefabChar::GetTexAtPatchIndex(int, bool) const { return nullptr; }