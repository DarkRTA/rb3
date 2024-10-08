#include "game/GameMode.h"
#include "game/GameMessages.h"
#include "obj/Dir.h"
#include "obj/DataUtl.h"
#include "os/PlatformMgr.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

GameMode* TheGameMode;

void GameModeInit(){
    MILO_ASSERT(TheGameMode == NULL, 0x1A);
    TheGameMode = new GameMode();
}

GameMode::GameMode(){
    SetName("gamemode", ObjectDir::sMainDir);
    SetMode("init");
}

GameMode::~GameMode(){

}

bool GameMode::InMode(Symbol target){
    if(mMode == target) return true;

    DataArray* modes = SystemConfig("modes");
    Symbol iter = mMode;
    
    while(modes->FindArray(iter, true)->FindArray(parent_mode, false)){
        iter = modes->FindArray(iter, true)->FindArray(parent_mode, true)->Sym(1);
        if(iter == target) return true;
    }
    
    return false;
}

DataNode GameMode::OnSetMode(const DataArray* a){
    MILO_ASSERT(a->Size() == 3, 0x45);
    SetMode(a->Sym(2));
    return DataNode(0);
}

void GameMode::SetMode(Symbol mode){
    if(mMode != mode){
        DataArray* cfg = SystemConfig("modes");
        HandleType(exit_msg);
        mMode = mode;
        DataArray* cloned = cfg->FindArray(mMode, true)->Clone(true, false, 0);
        if(cloned->FindArray(parent_only, false)){
            if(cloned->FindInt(parent_only)){
                MILO_FAIL("Trying to set mode %s, which is a parent_only mode!\n", mMode);
            }
        }

        Symbol iter = mMode;
        while(cfg->FindArray(iter, true)->FindArray(parent_mode, false)){
            iter = cfg->FindArray(iter, true)->FindArray(parent_mode, true)->Sym(1);
            DataMergeTags(cloned, cfg->FindArray(iter, true));
        }

        DataMergeTags(cloned, cfg->FindArray("defaults", true));
        SetTypeDef(cloned);
        cloned->Release();
        HandleType(enter_msg);
        ThePlatformMgr.unkce55 = Property("online_play_required", true)->Int(0);
        unk20 = Property("enable_overdrive", true)->Int(0);
        unk2c = InMode("h2h");
        unk30 = InMode("practice");
        unk34 = Property("can_lose", true)->Int(0);
        unk3c = Property("crowd_reacts", true)->Int(0);
        unk40 = Property("is_solo", true)->Int(0);
        unk44 = Property("disable_guitar_fx", true)->Int(0);
        unk48 = InMode("drum_trainer");
        unk50 = Property("enable_streak", true)->Int(0);
        unk58 = InMode("tutorial");
        unk5c = Property("load_chars", true)->Int(0);
        unk60 = Property("show_stars", true)->Int(0);
        unk64 = Property("has_song_sections", true)->Int(0);
        unk68 = Property("enable_whammy", true)->Int(0);
        unk6c = Property("end_with_song", true)->Int(0);
        unk70 = InMode("story");
        static ModeChangedMsg msg;
        MsgSource::Handle(msg, false);
    }
}

BEGIN_HANDLERS(GameMode)
    HANDLE_EXPR(in_mode, InMode(_msg->Sym(2)))
    HANDLE_EXPR(get_mode, mMode.Str())
    HANDLE(set_mode, OnSetMode)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_SUPERCLASS(MsgSource)
    HANDLE_CHECK(0xBC)
END_HANDLERS