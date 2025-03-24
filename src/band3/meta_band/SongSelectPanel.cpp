#include "meta_band/SongSelectPanel.h"
#include "AppMiniLeaderboardDisplay.h"
#include "game/BandUser.h"
#include "meta_band/Leaderboard.h"
#include "meta_band/MusicLibrary.h"
#include "meta_band/PlayerLeaderboards.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SongSortNode.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Task.h"
#include "os/ContentMgr.h"
#include "os/Debug.h"
#include "os/JoypadMsgs.h"
#include "ui/UIPanel.h"
#include "utl/Messages2.h"
#include "utl/Symbols.h"
#include "utl/Symbols3.h"

SongSelectPanel::SongSelectPanel()
    : mLeaderboard(0), unk48(0), unk4c(0), unk50(0), unk54(0), unk58(-1) {}

void SongSelectPanel::Load() {
    UIPanel::Load();
    TheMusicLibrary->OnLoad();
    TheContentMgr->StartRefresh();
}

bool SongSelectPanel::IsLoaded() const {
    return UIPanel::IsLoaded() && !TheContentMgr->RefreshInProgress();
}

void SongSelectPanel::FinishLoad() {
    UIPanel::FinishLoad();
    unk48 = mDir->Find<AppMiniLeaderboardDisplay>("leaderboard.mld", true);
    unk4c = TypeDef()->FindFloat("mini_leaderboard_rotation_off");
    unk50 = TypeDef()->FindFloat("mini_leaderboard_rotation_on");
}

bool SongSelectPanel::Exiting() const {
    return UIPanel::Exiting() || TheMusicLibrary->IsExiting();
}

void SongSelectPanel::Unload() {
    RELEASE(mLeaderboard);
    unk48 = nullptr;
    TheMusicLibrary->OnUnload();
    UIPanel::Unload();
}

DataNode SongSelectPanel::OnMsg(const ButtonDownMsg &) {
    if (TheMusicLibrary->IsPurchasing()) {
        return 1;
    } else if (TheContentMgr->RefreshInProgress()) {
        static Message msg("set_blocking", 1);
        UIPanel *clp = ObjectDir::Main()->Find<UIPanel>("content_loading_panel", true);
        MILO_ASSERT(clp, 0x6C);
        clp->Handle(msg, true);
        return 1;
    } else
        return DataNode(kDataUnhandled, 0);
}

Leaderboard *SongSelectPanel::GetLeaderboard(
    LocalBandUser *u, ScoreType s, int i, Leaderboard::Mode m
) {
    RELEASE(mLeaderboard);
    switch (TheMusicLibrary->GetHighlightedNode()->GetType()) {
    case kNodeSong:
        mLeaderboard =
            new PlayerSongLeaderboard(TheProfileMgr.GetProfileForUser(u), this, s, i);
        break;
    case kNodeSetlist:
        mLeaderboard =
            new PlayerBattleLeaderboard(TheProfileMgr.GetProfileForUser(u), this, i);
        break;
    default:
        MILO_FAIL("No leaderboard for the highlighted SongNodeType!");
        break;
    }
    MILO_ASSERT(mLeaderboard, 0x8A);
    mLeaderboard->SetMode(m, false);
    mLeaderboard->StartEnumerate();
    return mLeaderboard;
}

void SongSelectPanel::ResultSuccess(bool b1, bool b2, bool b3) {
    static Message success("lb_success", 0, 0, 0);
    success[0] = b1;
    success[1] = b2;
    success[2] = b3;
    HandleType(success);
}

void SongSelectPanel::ResultFailure() { HandleType(lb_failure_msg); }

void SongSelectPanel::RestartLeaderboardTimer() {
    unk58 = TheTaskMgr.UISeconds();
    static Message msg(set_mini_leaderboard_showing, 0);
    unk54 = false;
    msg[0] = 0;
    HandleType(msg);
}

void SongSelectPanel::CancelLeaderboardTimer() {
    unk58 = -1.0f;
    static Message msg(set_mini_leaderboard_showing, 0);
    unk54 = false;
    msg[0] = 0;
    HandleType(msg);
}

BEGIN_HANDLERS(SongSelectPanel)
    HANDLE_EXPR(
        get_leaderboard,
        GetLeaderboard(
            _msg->Obj<LocalBandUser>(2),
            (ScoreType)_msg->Int(3),
            _msg->Int(4),
            (Leaderboard::Mode)_msg->Int(5)
        )
    )
END_HANDLERS