#include "game/PresenceMgr.h"
#include "decomp.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "game/GameConfig.h"
#include "game/GameMode.h"
#include "meta_band/SessionMgr.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/PlatformMgr.h"
#include "ui/UI.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"

PresenceMgr ThePresenceMgr;

DECOMP_FORCEACTIVE(PresenceMgr, __FILE__, "TheSessionMgr", "required_song_options_chosen")

PresenceMgr::PresenceMgr()
    : unk1c(0), unk20(0), unk24(0), unk34(0), unk38(0), unk39(0), unk3c(0) {}

void PresenceMgr::UpdatePresence() {
    if (!TheGameConfig || !unk1c)
        return;
    else {
        Symbol mode = GetPresenceMode();
        bool inMode = false;
        FOREACH (it, unk2c) {
            if (TheGameMode->InMode(*it)) {
                inMode = true;
                break;
            }
        }
        std::vector<LocalBandUser *> &users = TheBandUserMgr->GetLocalBandUsers();
        FOREACH (it, users) {
            LocalBandUser *pUser = *it;
            MILO_ASSERT(pUser, 0xBD);
            if (ThePlatformMgr.IsUserSignedIn(pUser)) {
                bool noUserInSession = !TheSessionMgr->HasUser(pUser);
                GetPresenceContextFromMode(mode, noUserInSession);
                GetPlayModeContextFromUser(pUser, inMode);
            }
        }
    }
}

Symbol PresenceMgr::GetPresenceMode() {
    if (!unk1c)
        return gNullStr;
    else {
        int size = unk1c->Size();
        unk39 = false;
        for (int i = 1; i < size; i++) {
            DataArray *arr = unk1c->Array(i);
            if (arr->Size() > 0) {
                Symbol s50 = arr->Sym(0);
                bool b2 = true;
                for (int j = 1; j < arr->Size(); j++) {
                    DataArray *jArr = arr->Array(j);
                    Symbol s54 = jArr->Sym(0);
                    if (s54 == in_game) {
                        if (!unk38)
                            b2 = false;
                    } else if (s54 == screens) {
                        bool b1 = false;
                        int jSize = jArr->Size();
                        for (int k = 1; k < jSize; k++) {
                            Symbol s58 = jArr->Sym(k);
                            int depth = TheUI.PushDepth();
                            if (depth < 1) {
                                if (TheUI.CurrentScreen()) {
                                    if (s58 == TheUI.CurrentScreen()->Name()) {
                                        b1 = true;
                                        break;
                                    }
                                }
                            } else {
                                for (int n = 0; n < depth; n++) {
                                    if (TheUI.ScreenAtDepth(n)) {
                                        if (s58 == TheUI.ScreenAtDepth(n)->Name()) {
                                            b1 = true;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        if (!b1)
                            b2 = false;
                    } else if (s54 == gamemode) {
                        bool inMode = false;
                        int jSize = jArr->Size();
                        for (int k = 1; k < jSize; j++) {
                            if (TheGameMode->InMode(jArr->Sym(k))) {
                                inMode = true;
                                break;
                            }
                        }
                        if (!inMode)
                            b2 = false;
                    } else if (s54 == override_play_mode) {
                        unk39 = true;
                        unk3c = jArr->Int(1);
                    }
                    if (!b2)
                        break;
                }
                if (b2)
                    return s50;
            }
        }
        return gNullStr;
    }
}

int PresenceMgr::GetPresenceContextFromMode(Symbol s, bool b) {
    if (!unk1c)
        return -1;
    else {
        return unk20->FindArray(s)->Int(b + 1);
    }
}

int PresenceMgr::GetPlayModeContextFromUser(const LocalBandUser *, bool) {
    Symbol("force_use_cymbals");
    Symbol("force_dont_use_cymbals");
    MILO_WARN("default");
}

DataNode PresenceMgr::OnPresenceChange(DataArray *a) {
    if (!a)
        return 0;
    else {
        UpdatePresence();
        return 0;
    }
}

BEGIN_HANDLERS(PresenceMgr)
    HANDLE(current_screen_changed, OnPresenceChange)
    HANDLE(session_ready, OnPresenceChange)
    HANDLE(add_local_user_result_msg, OnPresenceChange)
    HANDLE(signin_changed, OnPresenceChange)
    HANDLE(local_user_left, OnPresenceChange)
    HANDLE(required_song_options_chosen, OnPresenceChange)
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x22F)
END_HANDLERS