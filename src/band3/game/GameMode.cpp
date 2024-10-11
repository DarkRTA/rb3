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
            if(cloned->FindArray(parent_only, true)->Int(1)){
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
        ThePlatformMgr.unkce55 = Property("online_play_required", true)->Int();
        mOverdriveEnabled = Property("enable_overdrive", true)->Int();
        mH2HArrangement = InMode("h2h");
        mIsPractice = InMode("practice");
        mCanLose = Property("can_lose", true)->Int();
        mCrowdReacts = Property("crowd_reacts", true)->Int();
        mIsSolo = Property("is_solo", true)->Int();
        mDisableGuitarFx = Property("disable_guitar_fx", true)->Int();
        mIsDrumTrainer = InMode("drum_trainer");
        mEnableStreak = Property("enable_streak", true)->Int();
        mIsTutorial = InMode("tutorial");
        mLoadChars = Property("load_chars", true)->Int();
        mShowStars = Property("show_stars", true)->Int();
        mHasSongSections = Property("has_song_sections", true)->Int();
        mEnableWhammy = Property("enable_whammy", true)->Int();
        mEndWithSong = Property("end_with_song", true)->Int();
        mIsStory = InMode("story");
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
