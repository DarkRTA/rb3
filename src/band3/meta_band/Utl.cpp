#include "meta_band/Utl.h"
#include "decomp.h"
#include "game/Defines.h"
#include "obj/Utl.h"
#include "SongStatusMgr.h"
#include "beatmatch/TrackType.h"
#include "meta_band/SessionMgr.h"
#include "obj/Data.h"
#include "obj/DataUtl.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "os/System.h"
#include "utl/Symbols.h"
#include "ui/UIPanel.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include <obj/DataFunc.h>
#include <os/PlatformMgr.h>

static int kMinContentLevel = 2;

static DataNode OnToggleFakeLeaderboardUploadFailure(DataArray *da) {
    SongStatusMgr::sFakeLeaderboardUploadFailure =
        !SongStatusMgr::sFakeLeaderboardUploadFailure;
    Hmx::Object *cheatObj = ObjectDir::Main()->Find<Hmx::Object>("cheat_display", true);
    if (cheatObj) {
        static Message msg("show_bool", "Fake leaderboard upload failure", 0);
        msg[1] = SongStatusMgr::sFakeLeaderboardUploadFailure;
        cheatObj->Handle(msg, false);
    }
    return 0;
}

static DataNode OnGetFontCharFromInstrument(DataArray *);
static DataNode OnGetFontCharFromControllerType(DataArray *);
static DataNode OnGetFontCharFromTrackType(DataArray *);
static DataNode OnGetFontCharFromScoreType(DataArray *);
static DataNode OnGetFontCharForHarmonyMics(DataArray *);
static DataNode OnIsLeaderLocal(DataArray *);
static DataNode OnIsVignette(DataArray *);
static DataNode OnSafeName(DataArray *);
static DataNode OnAllowedToAccessContent(DataArray *);

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

bool IsLeaderLocal() {
    if (TheSessionMgr)
        return TheSessionMgr->IsLeaderLocal();
    else
        return true;
}

static DataNode OnIsLeaderLocal(DataArray *) { return IsLeaderLocal(); }

bool IsVignette(UIPanel *panel) {
    if (!panel)
        return false;
    else {
        Hmx::Object *old_this = DataSetThis(panel);
        bool ret = false;
        if (panel->TypeDef()) {
            DataArray *fileArr = panel->TypeDef()->FindArray(file, false);
            if (fileArr) {
                if (strstr(fileArr->Str(1), "world/vignette/")) {
                    ret = true;
                }
            }
        }
        DataSetThis(old_this);
        return ret;
    }
}

static DataNode OnIsVignette(DataArray *da) { return IsVignette(da->Obj<UIPanel>(1)); }

static DataNode OnSafeName(DataArray *da) { return SafeName(da->Obj<Hmx::Object>(1)); }

static DataNode OnGetFontCharFromInstrument(DataArray *da) {
    Symbol inst = da->Sym(1);
    int idx = da->Size() > 2 ? da->Int(2) : 0;
    return GetFontCharFromInstrument(inst, idx);
}

static DataNode OnGetFontCharFromControllerType(DataArray *da) {
    ControllerType cty = (ControllerType)da->Int(1);
    int idx = da->Size() > 2 ? da->Int(2) : 0;
    return GetFontCharFromControllerType(cty, idx);
}

static DataNode OnGetFontCharFromTrackType(DataArray *da) {
    TrackType tty = (TrackType)da->Int(1);
    int idx = da->Size() > 2 ? da->Int(2) : 0;
    return GetFontCharFromTrackType(tty, idx);
}

static DataNode OnGetFontCharFromScoreType(DataArray *da) {
    ScoreType sty = (ScoreType)da->Int(1);
    int idx = da->Size() > 2 ? da->Int(2) : 0;
    return GetFontCharFromScoreType(sty, idx);
}

const char *GetFontCharFromInstrument(Symbol instrument, int idx) {
    MILO_ASSERT(!instrument.Null(), 0xB7);
    return GetFontCharFromTrackType(SymToTrackType(instrument), idx);
}

const char *GetFontCharFromScoreType(ScoreType scoreType, int idx) {
    switch (scoreType) {
    case kScoreBand:
        return "j";
    case kScoreDrum:
    case kScoreBass:
    case kScoreGuitar:
    case kScoreVocals:
    case kScoreKeys:
    case kScoreRealGuitar:
    case kScoreRealBass:
    case kScoreRealKeys:
        return GetFontCharFromTrackType(ScoreTypeToTrackType(scoreType), idx);
    case kScoreRealDrum:
        return GetFontCharForProDrums(idx);
    case kScoreHarmony:
        return GetFontCharForHarmonyMics(3, idx);
    default:
        MILO_WARN("Invalid ScoreType\n");
        return gNullStr;
    }
}

const char *GetFontCharFromTrackType(TrackType trackType, int idx) {
    MILO_ASSERT_RANGE(trackType, 0, kNumTrackTypes + 1, 0xD9);
    switch (trackType) {
    case kTrackDrum:
    case kTrackGuitar:
    case kTrackBass:
    case kTrackVocals:
    case kTrackKeys:
    case kTrackRealKeys:
    case kTrackRealGuitar:
    case kTrackRealBass:
        return SystemConfig(instrument_icons, TrackTypeToSym(trackType))->Str(idx + 1);
    case kTrackNone:
        MILO_WARN("GetFontCharFromTrackType passed kTrackNone\n");
        return "_";
    default:
        MILO_FAIL("Invalid TrackType specified: %d", (int)trackType);
        return nullptr;
    }
}

const char *GetFontCharFromControllerType(ControllerType controllerType, int idx) {
    MILO_ASSERT_RANGE(controllerType, 0, kNumControllerTypes, 0xFB);
    return GetFontCharFromTrackType(ControllerTypeToTrackType(controllerType, false), idx);
}

static DataNode OnGetFontCharForHarmonyMics(DataArray *da) {
    int i1 = da->Int(1);
    int idx = da->Size() > 2 ? da->Int(2) : 0;
    return GetFontCharForHarmonyMics(i1, idx);
}

const char *GetFontCharForHarmonyMics(int num_mics, int idx) {
    switch (num_mics) {
    case 2:
        return SystemConfig(instrument_icons, harmony_2)->Str(idx + 1);
    case 3:
        return SystemConfig(instrument_icons, harmony_3)->Str(idx + 1);
    default:
        MILO_FAIL("Invalid number of mics: %i", num_mics);
        return nullptr;
    }
}

#pragma push
#pragma force_active on
inline const char *GetFontCharForProDrums(int idx) {
    return SystemConfig(instrument_icons, drum_pro)->Str(idx + 1);
}
#pragma pop

// enum TrackType {
//     kTrackDrum = 0,
//     kTrackGuitar = 1,
//     kTrackBass = 2,
//     kTrackVocals = 3,
//     kTrackKeys = 4,
//     kTrackRealKeys = 5,
//     kTrackRealGuitar = 6,
//     kTrackRealGuitar22Fret = 7,
//     kTrackRealBass = 8,
//     kTrackRealBass22Fret = 9,
//     kTrackNone = 10,
//     kNumTrackTypes = 10,
//     kTrackPending = 11,
//     kTrackPendingVocals = 12
// };

const char *GetUserFontChar(BandUser *user, MetaPerformer *perf, int idx) {
    Symbol inst(gNullStr);
    TrackType ty = user->GetTrackType();
    if (ty == kTrackNone || ty == kTrackPending || ty == kTrackPendingVocals) {
        ty = ControllerTypeToTrackType(user->GetControllerType(), false);
    }
    switch (ty) {
    case kTrackVocals:
        if (perf && !perf->IsSetComplete() && perf->IsNowUsingVocalHarmony()) {
            int parts = perf->GetSetlistMaxVocalParts();
            if (parts == 2)
                inst = harmony_2;
            else
                inst = harmony_3;
        }
        break;
    case kTrackDrum:
        if (user->GetPreferredScoreType() == 6) {
            inst = drum_pro;
        }
    default:
        break;
    }
    if (inst == gNullStr) {
        return GetFontCharFromTrackType(ty, idx);
    } else {
        return SystemConfig(instrument_icons, inst)->Str(idx + 1);
    }
}

int MaxAllowedHmxMaturityLevel();

bool AllowedToAccessContent(int level) {
    if (level <= kMinContentLevel) {
        return true;
    } else {
        int maxAllowedLevel = MaxAllowedHmxMaturityLevel();
        return level <= maxAllowedLevel;
    }
}

static DataNode OnAllowedToAccessContent(DataArray *da) {
    int level = da->Int(1);
    bool allowedToAccessContent = AllowedToAccessContent(level);
    return DataNode(allowedToAccessContent);
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