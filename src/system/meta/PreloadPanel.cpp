#include "meta/PreloadPanel.h"
#include "meta/SongMgr.h"
#include "utl/Symbols.h"

FileCache* PreloadPanel::sCache;

PreloadPanel::PreloadPanel() : unk3c(0), unk48(0), mAppReadFailureHandler(0), unk58(0), unk68(0) {
    if(!sCache) sCache = new FileCache(0x500000, kLoadBack, true);
}

PreloadPanel::~PreloadPanel(){

}

void PreloadPanel::SetTypeDef(DataArray* da){
    if(TypeDef() != da){
        UIPanel::SetTypeDef(da);
        CheckTypeDef("song_mgr");
        CheckTypeDef("current_song");
        CheckTypeDef("on_preload_ok");
        CheckTypeDef("preload_files");
    }
}

void PreloadPanel::CheckTypeDef(Symbol s){
    if(!TypeDef()->FindArray(s, false)){
        MILO_WARN("PreloadPanel %s missing %s handler (%s)", Name(), s, TypeDef()->File());
    }
}

void PreloadPanel::Load(){
    UIPanel::Load();
    unk3c = 0;
    TheContentMgr->RegisterCallback(this, false);
    mAppReadFailureHandler = TheContentMgr->SetReadFailureHandler(this);
    MILO_ASSERT(mAppReadFailureHandler, 0x57);
    unk58 = false;
    unk5c = gNullStr;
    Symbol songSym = TypeDef()->FindSym(current_song);
    if(songSym.Null()) MILO_WARN("Trying to preload null song");
    SongMgr* mgr = TypeDef()->FindArray(song_mgr, true)->Obj<SongMgr>(1);
    // assert song_mgr
    unk4c.clear();
    unk68 = false;
}

Symbol PreloadPanel::CurrentSong() const {
    return TypeDef()->FindSym(current_song);
}