#include "meta_band/CharCache.h"
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandCharacter.h"
#include "bandobj/BandWardrobe.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "utl/FilePath.h"
#include "utl/Loader.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"

CharCache* TheCharCache;

void CharCache::Init(){
    TheCharCache = new CharCache();
    TheCharCache->InitMe();
}

CharCache::~CharCache(){

}

CharCache::CharCache() : unk28(0) {

}

void CharCache::InitMe(){
    FilePathTracker tracker("char");
    SetName("char_cache", ObjectDir::Main());
    unk1c.LoadFile(FilePath("../world/shared/chars.milo"), false, true, kLoadFront, false);
}

void CharCache::Request(int idx, const std::vector<BandCharDesc*>& descs, bool b1, bool b2){
    if(!unk28){
        BandCharacter* bchar = GetCharacter(idx);
        bchar->CopyCharDesc(descs.front());
        bchar->StartLoad(true, b1, b2);
    }
}

void CharCache::RecomposePatches(int idx, BandCharDesc* desc, int i2){
    GetCharacter(idx)->RecomposePatches(desc, i2);
}

void CharCache::RecomposeCharsWithPatchIx(int idx){
    if(idx >= 0){
        for(int i = 0; i < 4; i++){
            BandCharacter* c = GetCharacter(i);
            MILO_ASSERT(c, 0x60);
        }
    }
}

BandCharacter* CharCache::GetCharacter(int slot){
    MILO_ASSERT(slot >= 0 && slot < BandWardrobe::kNumTargets, 0x76);
    return unk1c->Find<BandCharacter>(MakeString("player%d", slot), true);
}

int CharCache::FindSlot(BandCharacter* bchar){
    int i = 0;
    for(; i < 4; i++){
        if(bchar == GetCharacter(i)) break;
    }
    return i;
}

bool CharCache::CharactersAreLoading(){
    for(int i = 0; i < 4; i++){
        if(GetCharacter(i)->IsLoading()) return true;
    }
    return false;
}

BEGIN_HANDLERS(CharCache)
    HANDLE(get_patch_tex, OnGetPatchTex)
    HANDLE_ACTION(recompose_chars_with_patch_ix, RecomposeCharsWithPatchIx(_msg->Int(2)))
    HANDLE_EXPR(characters_are_loading, CharactersAreLoading())
    HANDLE_ACTION(lock, Lock(_msg->Int(2), _msg->Size() > 3 ? _msg->Int(3) : false))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xAF)
END_HANDLERS

DataNode CharCache::OnGetPatchTex(DataArray* arr){
    
}