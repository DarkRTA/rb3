#include "system/utl/Symbol.h"
#include <obj/DataFunc.h>
#include <os/PlatformMgr.h>

static int kMinContentLevel = 2;

bool IsLeaderLocal() {
    // return TheSessionMgr->IsLeaderLocal(); -- uncomment when SessionMgr is implemented
    // to match this function
    return false;
}

int MaxAllowedHmxMaturityLevel() {
    if (ThePlatformMgr.unkce6b != 0) {
        return 4;
    }
    if (kMinContentLevel <= 4) {
        return 4;
    }
    return kMinContentLevel;
}

bool AllowedToAccessContent(int level) {
    if (level <= kMinContentLevel) {
        return true;
    } else {
        int maxAllowedLevel = MaxAllowedHmxMaturityLevel();
        return level <= maxAllowedLevel;
    }
}

static DataNode OnGetFontCharFromInstrument(DataArray *da) {}

static DataNode OnGetFontCharFromControllerType(DataArray *da) {}

static DataNode OnGetFontCharFromTrackType(DataArray *da) {}

static DataNode OnGetFontCharFromScoreType(DataArray *da) {}

static DataNode OnGetFontCharForHarmonyMics(DataArray *da) {}

static DataNode OnIsLeaderLocal(DataArray *da) {
    bool isLeaderLocal = IsLeaderLocal();
    return DataNode(isLeaderLocal);
}

static DataNode OnIsVignette(DataArray *da) {}

static DataNode OnToggleFakeLeaderboardUploadFailure(DataArray *da) {}

static DataNode OnSafeName(DataArray *da) {}

static DataNode OnAllowedToAccessContent(DataArray *da) {
    int level = da->Int(1);
    bool allowedToAccessContent = AllowedToAccessContent(level);
    return DataNode(allowedToAccessContent);
}

void UtlInit() {
    DataRegisterFunc("cnv_instrumenttoicon", OnGetFontCharFromInstrument);
    DataRegisterFunc(
        "get_font_char_from_controller_type", OnGetFontCharFromControllerType
    );
    DataRegisterFunc("get_font_char_from_track_type", OnGetFontCharFromTrackType);
    DataRegisterFunc("get_font_char_from_score_type", OnGetFontCharFromScoreType);
    DataRegisterFunc("get_font_char_for_harmony_mics", OnGetFontCharForHarmonyMics);
    DataRegisterFunc("is_leader_local", OnIsLeaderLocal);
    DataRegisterFunc("is_vignette", OnIsVignette);
    DataRegisterFunc(
        "toggle_fake_leaderboard_upload_failure", OnToggleFakeLeaderboardUploadFailure
    );
    DataRegisterFunc("safe_name", OnSafeName);
    DataRegisterFunc("allowed_to_access_content", OnAllowedToAccessContent);
}