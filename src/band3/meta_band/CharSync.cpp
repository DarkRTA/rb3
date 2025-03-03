#include "meta_band/CharSync.h"
#include "bandobj/BandCharDesc.h"
#include "bandobj/BandDirector.h"
#include "game/Band.h"
#include "game/BandUser.h"
#include "game/BandUserMgr.h"
#include "meta_band/BandUI.h"
#include "meta_band/CharCache.h"
#include "meta_band/ClosetMgr.h"
#include "meta_band/OvershellPanel.h"
#include "meta_band/PrefabMgr.h"
#include "meta_band/ProfileMessages.h"
#include "meta_band/CharData.h"
#include "meta_band/ProfileMgr.h"
#include "movie/Splash.h"
#include "obj/Data.h"
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "rndwii/Tex.h"
#include "ui/UI.h"
#include "ui/UIScreen.h"
#include "utl/Std.h"
#include "utl/Symbols.h"

CharSync *TheCharSync;

void CharSync::Init(BandUserMgr *mgr) {
    mgr = mgr ? mgr : TheBandUserMgr;
    TheCharSync = new CharSync(mgr);
    TheCharSync->SetName("char_sync", ObjectDir::Main());
}

CharSync::CharSync(BandUserMgr *mgr) : mUserMgr(mgr) {
    MILO_ASSERT(mUserMgr, 0x35);
    TheProfileMgr.AddSink(this, PrimaryProfileChangedMsg::Type());
    TheProfileMgr.AddSink(this, ProfileChangedMsg::Type());
}

CharSync::~CharSync() {
    TheProfileMgr.RemoveSink(this, ProfileChangedMsg::Type());
    TheProfileMgr.RemoveSink(this, PrimaryProfileChangedMsg::Type());
}

#pragma push
#pragma dont_inline on
void CharSync::UpdateCharCache() {
    OvershellPanel *overshell = TheBandUI.GetOvershell();
    MILO_ASSERT(overshell, 0x47);

    if (overshell->InSong() || TheSplasher || TheUI.InTransition()
        || !TheUI.CurrentScreen()
        || streq(TheUI.CurrentScreen()->Name(), "part_difficulty_screen")
        || (TheUI.TransitionScreen()
            && streq(TheUI.TransitionScreen()->Name(), "part_difficulty_screen")))
        return;

    UIScreen *screen = TheUI.CurrentScreen();
    Message msg("block_char_cache");
    DataNode handled = screen->HandleType(msg);
    if (handled.Type() != kDataUnhandled && handled.LiteralInt() != 0)
        return;

    std::vector<CharData *> data48;
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    PrefabMgr *prefabMgr = PrefabMgr::GetPrefabMgr();
    for (int i = 0; i < 4; i++) {
        CharData *charDesc = nullptr;
        if (profile) {
            const StandIn &standin = profile->GetStandIn(i);
            if (standin.IsNone())
                charDesc = nullptr;
            else if (standin.IsPrefabCharacter()) {
                charDesc = prefabMgr->GetPrefab(standin.GetName());
            } else {
                MILO_ASSERT(standin.IsCustomCharacter(), 0x7E);
                charDesc = profile->GetCharFromGuid(standin.GetGuid());
                MILO_ASSERT(charDesc, 0x81);
            }
        }
        data48.push_back(charDesc);
    }

    std::vector<CharData *> prefabsBySlot;
    for (int i = 0; i < 4; i++) {
        CharData *target = prefabMgr->GetDefaultPrefab(i);
        if (std::find(data48.begin(), data48.end(), target) == data48.end()) {
            prefabsBySlot.push_back(target);
        } else
            prefabsBySlot.push_back(nullptr);
    }

    std::vector<BandUser *> users58;
    mUserMgr->GetParticipatingBandUsers(users58);
    for (int i = 0; i < users58.size(); i++) {
        CharData *target = users58[i]->GetChar();
        std::vector<CharData *>::iterator it48 =
            std::find(data48.begin(), data48.end(), target);
        if (it48 != data48.end())
            *it48 = nullptr;
        std::vector<CharData *>::iterator it50 =
            std::find(prefabsBySlot.begin(), prefabsBySlot.end(), target);
        if (it50 != prefabsBySlot.end())
            *it50 = nullptr;
    }

    std::list<CharData *> data60;
    std::list<CharData *> prefabBackups;
    for (int i = 0; i < 4; i++) {
        BandUser *curUser = mUserMgr->GetUserFromSlot(i);
        if (curUser && curUser->HasChar()) {
            if (prefabsBySlot[i]) {
                prefabBackups.push_back(prefabsBySlot[i]);
                prefabsBySlot[i] = nullptr;
            }
            if (data48[i]) {
                data60.push_back(data48[i]);
                data48[i] = nullptr;
            }
        } else if (data48[i] && prefabsBySlot[i]) {
            prefabBackups.push_back(prefabsBySlot[i]);
            prefabsBySlot[i] = nullptr;
        }
    }

    for (int n = 0; n < 4; n++) {
        bool inCloset = false;
        std::vector<BandCharDesc *> descs70;
        if (TheBandDirector->IsMusicVideo()) {
            BandCharDesc *curDesc = Hmx::Object::New<BandCharDesc>();
            curDesc->GetHead().mHide = true;
            descs70.push_back(curDesc);
            TheCharCache->Request(n, descs70, false, false);
            delete curDesc;
            std::vector<WiiTex *> tex78;
            std::set<WiiTex *>::iterator iter;
            for (iter = gRenderTextureSet.begin(); iter != gRenderTextureSet.end();
                 iter++) {
                if (strstr((*iter)->Name(), "output")) {
                    tex78.push_back(*iter);
                }
            }
            FOREACH (it, tex78) {
                (*it)->DeleteSurface();
            }
            continue;
        } else {
            BandUser *curUser = mUserMgr->GetUserFromSlot(n);
            if (curUser) {
                if (ClosetMgr::GetClosetMgr()->GetUser() == curUser)
                    continue;
            }
            if (n == 0) {
                if (ClosetMgr::GetClosetMgr()->InNoUserMode())
                    continue;
            }
            if (curUser && curUser->HasChar()) {
                inCloset = TheCharCache->GetCharacter(n)->InCloset();
                descs70.push_back(curUser->GetChar()->GetBandCharDesc());
            } else {
                CharData *npc;
                if (data48[n]) {
                    npc = data48[n];
                    MILO_ASSERT(!prefabsBySlot[n], 0x114);
                } else {
                    if (!data60.empty()) {
                        npc = data60.front();
                        data60.pop_front();
                        if (prefabsBySlot[n]) {
                            prefabBackups.push_back(prefabsBySlot[n]);
                        }
                    } else {
                        if (prefabsBySlot[n]) {
                            npc = prefabsBySlot[n];
                        } else {
                            MILO_ASSERT(!prefabBackups.empty(), 0x128);
                            npc = prefabBackups.front();
                            prefabBackups.pop_front();
                        }
                    }
                }
                MILO_ASSERT(npc, 0x12D);
                descs70.push_back(npc->GetBandCharDesc());
            }
            TheCharCache->Request(n, descs70, inCloset, false);
        }
    }
}
#pragma pop

DataNode CharSync::OnMsg(const PrimaryProfileChangedMsg &) {
    UpdateCharCache();
    return 1;
}

DataNode CharSync::OnMsg(const ProfileChangedMsg &msg) {
    BandProfile *p = msg.GetProfile();
    if (p) {
        LocalBandUser *u = msg.GetProfile()->GetLocalBandUser();
        CharData *data = nullptr;
        if (p)
            data = p->GetLastCharUsed();
        if (data && TheBandUserMgr->IsCharAvailable(data)) {
            u->SetChar(data);
        }
    }
    UpdateCharCache();
    return 1;
}

BEGIN_HANDLERS(CharSync)
    HANDLE_ACTION(update_char_cache, UpdateCharCache())
    HANDLE_MESSAGE(PrimaryProfileChangedMsg)
    HANDLE_MESSAGE(ProfileChangedMsg)
    HANDLE_CHECK(0x15F)
END_HANDLERS