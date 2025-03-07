#include "meta_band/EditSetlistPanel.h"
#include "MusicLibrary.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "meta_band/BandProfile.h"
#include "meta_band/ProfileMgr.h"
#include "meta_band/SaveLoadManager.h"
#include "meta_band/SavedSetlist.h"
#include "net_band/RockCentralMsgs.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "os/Debug.h"
#include "os/PlatformMgr.h"
#include "ui/UIPanel.h"
#include "ui/UIScreen.h"
#include "utl/Locale.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols2.h"
#include "utl/Symbols3.h"
#include "utl/Symbols4.h"
#include "utl/UTF8.h"

EditSetlistPanel::EditSetlistPanel()
    : unk50(kScoreBand), unk54(0), unk58(3), unk64(0), unk80(-1), unk84(-1), mProfile(0),
      mEditingSetlist(0), unk90(0), unk94(0), unk98(0), unk9c(0),
      mEditState((EditState)8), unka4((FailureReason)6) {}

EditSetlistPanel::~EditSetlistPanel() { CleanupStringVerify(); }

void EditSetlistPanel::Enter() {
    UIPanel::Enter();
    SetEditState((EditState)0);
}

DataNode EditSetlistPanel::OnMsg(const UITransitionCompleteMsg &msg) {
    MILO_ASSERT(mEditState == kEntering, 0x3B);
    switch (unk9c) {
    case 0:
        SetEditState((EditState)2);
        break;
    case 1:
        MILO_ASSERT(mEditingSetlist, 0x44);
        SetEditState((EditState)3);
        break;
    case 2:
        SetEditState((EditState)1);
        break;
    default:
        MILO_FAIL("Bad mode %i!");
        break;
    }
    return DataNode(kDataUnhandled, 0);
}

void EditSetlistPanel::Poll() {
    UIPanel::Poll();
    if (mEditState == 4 && !unk98 && !ThePlatformMgr.IsCheckingProfanity()) {
        VerifyStrings(mSetlistName.c_str(), mSetlistDescription.c_str());
        unk98 = true;
    }
}

bool EditSetlistPanel::Exiting() const { return UIPanel::Exiting(); }

void EditSetlistPanel::Unload() {
    CleanupStringVerify();
    unk68.Clear();
    UIPanel::Unload();
}

void EditSetlistPanel::CleanupStringVerify() {
    if (unk90) {
        delete[] unk90[0];
        delete[] unk90[1];
        delete[] unk90;
        unk90 = 0;
    }
    if (unk94) {
        delete[] unk94;
        unk94 = 0;
    }
}

bool EditSetlistPanel::CreateSetlist(bool b1) {
    MILO_ASSERT(GetState() != kUp, 0xC0);
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    if (profile) {
        mProfile = profile;
        unk9c = 0;
        unk64 = b1;
        mSetlistName = Localize(setlist_default_name, nullptr);
        mSetlistDescription = Localize(setlist_default_desc, nullptr);
        mSetlistArt.patchType = 0;
        return true;
    } else
        return false;
}

bool EditSetlistPanel::EditSetlist(LocalBandUser *user, LocalSavedSetlist *setlist) {
    MILO_ASSERT(GetState() != kUp, 0xD5);
    MILO_ASSERT(user, 0xD6);
    MILO_ASSERT(setlist, 0xD7);
    BandProfile *profile = TheProfileMgr.GetProfileForUser((const LocalUser *)user);
    if (user->CanSaveData() && profile) {
        unk9c = 1;
        mSetlistName = setlist->mTitle.c_str();
        mSetlistDescription = setlist->mDescription.c_str();
        mSetlistArt = setlist->mArt;
        mProfile = profile;
        mEditingSetlist = setlist;
        return true;
    } else
        return false;
}

bool EditSetlistPanel::CreateBattle() {
    MILO_ASSERT(GetState() != kUp, 0xEE);
    BandProfile *profile = TheProfileMgr.GetPrimaryProfile();
    if (profile) {
        LocalBandUser *user = profile->GetAssociatedLocalBandUser();
        if (user && user->IsSignedInOnline()) {
            unk9c = 2;
            mProfile = profile;
            mSetlistName = Localize(battle_default_name, nullptr);
            mSetlistDescription = Localize(battle_default_desc, nullptr);
            unk50 = kScoreBand;
            unk54 = 7;
            mSetlistArt.patchType = 0;
            unk84 = -1;
            return true;
        }
    }
    return false;
}

Symbol EditSetlistPanel::GetMessageToken() {
    switch (mEditState) {
    case 7:
        switch (unk9c) {
        case 0:
            return create_setlist_success;
        case 1:
            return edit_setlist_success;
        case 2:
            return create_battle_success;
        default:
            MILO_FAIL("Bad mode %i!");
            return gNullStr;
        }
        break;
    case 8:
        switch (unka4) {
        case 0:
            return error_battle_limit_reached;
        case 1:
            return error_setlist_limit_reached;
        case 2:
            return error_setlist_title_empty;
        case 3:
            return error_setlist_description_empty;
        case 4:
            return unk9c == 2 ? error_battle_title_profane : error_setlist_title_profane;
        case 5:
            return unk9c == 2 ? error_battle_description_profane
                              : error_setlist_description_profane;
        case 6:
        case 7:
            return error_setlist_unknown;
        default:
            MILO_FAIL("Bad fail reason %i!");
            return gNullStr;
        }
        break;
    default:
        MILO_FAIL("In bad EditState %i in GetMessageToken!", mEditState);
        return gNullStr;
    }
}

Symbol EditSetlistPanel::GetTitleToken() {
    switch (unk9c) {
    case 0:
        return unk64 ? setlist_save_share : setlist_save_local;
    case 1:
        return edit_setlist;
    case 2:
        return setlist_save_battle;
    default:
        MILO_FAIL("Bad mode %i!");
        return gNullStr;
    }
}

RndTex *EditSetlistPanel::GetArtTex() {
    RndTex *tex = nullptr;
    if (mSetlistArt.patchType == 1) {
        MILO_ASSERT(mProfile, 0x18A);
        tex = mProfile->GetTexAtPatchIndex(mSetlistArt.patchIndex);
    }
    return tex;
}

void EditSetlistPanel::DoneEditing() {
    if (mSetlistName.empty()) {
        FailWithReason((FailureReason)2);
    } else if (mSetlistDescription.empty()) {
        FailWithReason((FailureReason)3);
    } else {
        switch (unk9c) {
        case 0:
            MILO_ASSERT(mProfile, 0x19D);
            mEditingSetlist = mProfile->AddSavedSetlist(
                mSetlistName.c_str(),
                mSetlistDescription.c_str(),
                unk64,
                mSetlistArt,
                TheMusicLibrary->GetSetlist()
            );
            TheSaveLoadMgr->AutoSave();
            SetEditState((EditState)7);
            break;
        case 1:
            MILO_ASSERT(mEditingSetlist, 0x1A6);
            MILO_ASSERT(mProfile, 0x1A7);
            mEditingSetlist->SetTitle(mSetlistName.c_str());
            mEditingSetlist->SetDescription(mSetlistDescription.c_str());
            mEditingSetlist->mArt = mSetlistArt;
            mEditingSetlist->unk68++;
            mProfile->SetlistChanged(mEditingSetlist);
            TheSaveLoadMgr->AutoSave();
            SetEditState((EditState)7);
            break;
        case 2:
            SetEditState((EditState)4);
            break;
        default:
            MILO_FAIL("Bad mode %i!");
            break;
        }
    }
}

void EditSetlistPanel::VerifyStrings(const char *name, const char *desc) {
    unk90 = new unsigned short *[2];
    unsigned short *us = new unsigned short[strlen(name) + 1];
    UTF8toUTF16(us, name);
    unk90[0] = us;
    unsigned short *us2 = new unsigned short[strlen(desc) + 1];
    UTF8toUTF16(us2, desc);
    unk90[1] = us2;
    unk94 = new char[2];
    if (!ThePlatformMgr.StartProfanity((const unsigned short **)unk90, 2, unk94, this)) {
        CleanupStringVerify();
        FailWithReason((FailureReason)7);
    }
}

void EditSetlistPanel::VerifyStringsComplete(bool b1, bool b2) {
    MILO_ASSERT(mEditState == kCheckingProfanity, 0x2BD);
    CleanupStringVerify();
    if (!b1)
        FailWithReason((FailureReason)4);
    else if (!b2)
        FailWithReason((FailureReason)5);
    else {
        if (GetArtTex()) {
            SetEditState((EditState)5);
        } else
            SetEditState((EditState)6);
    }
}

void EditSetlistPanel::FailWithReason(FailureReason r) {
    unka4 = r;
    SetEditState((EditState)8);
}

int EditSetlistPanel::SymToDayCount(Symbol s) {
    DataArray *a = Property(expiration_data, true)->Array();
    return a->FindInt(s);
}

int EditSetlistPanel::SymToTimeUnits(Symbol s) {
    if (s == seconds)
        return 0;
    else if (s == minutes)
        return 1;
    else if (s == hours)
        return 2;
    else if (s == weeks)
        return 4;
    else
        return 3;
}

Symbol EditSetlistPanel::DayCountToSym(int days) {
    DataArray *a = Property(expiration_data, true)->Array();
    for (int i = 0; i < a->Size(); i++) {
        DataArray *a2 = a->Array(i);
        if (a2->Int(1) == days)
            return a2->Sym(0);
    }
    MILO_FAIL("No matching sym for %i days in EditSetlistPanel::DayCountToSym", days);
    return gNullStr;
}

#pragma push
#pragma dont_inline on
BEGIN_HANDLERS(EditSetlistPanel)
    HANDLE_EXPR(create_setlist, CreateSetlist(_msg->Int(2)))
    HANDLE_EXPR(
        edit_setlist,
        EditSetlist(_msg->Obj<LocalBandUser>(2), _msg->Obj<LocalSavedSetlist>(3))
    )
    HANDLE_EXPR(create_battle, CreateBattle())
    HANDLE_ACTION(done_editing, DoneEditing())
    HANDLE_EXPR(editing_setlist, unk9c == 1)
    HANDLE_ACTION(message_ok, MessageOK())
    HANDLE_EXPR(get_message_token, GetMessageToken())
    HANDLE_EXPR(get_title_token, GetTitleToken())
    HANDLE_EXPR(get_art_tex, GetArtTex())
    HANDLE_EXPR(get_instrument_list_sym, ScoreTypeToSym(unk50))
    HANDLE_EXPR(get_expiration_list_sym, DayCountToSym(unk54))
    HANDLE_ACTION(set_instrument_to_list_sym, unk50 = SymToScoreType(_msg->Sym(2)))
    HANDLE_ACTION(set_expiration_to_list_sym, unk54 = SymToDayCount(_msg->Sym(2)))
    HANDLE_ACTION(set_expiration_val_cheat, unk54 = _msg->Int(2))
    HANDLE_ACTION(set_expiration_units_cheat, unk58 = SymToTimeUnits(_msg->Sym(2)))
    HANDLE_MESSAGE(RockCentralOpCompleteMsg)
    HANDLE_MESSAGE(DWCProfanityResultMsg)
    HANDLE_MESSAGE(UITransitionCompleteMsg)
    HANDLE_SUPERCLASS(UIPanel)
    HANDLE_CHECK(0x37D)
END_HANDLERS
#pragma pop

BEGIN_PROPSYNCS(EditSetlistPanel)
    SYNC_PROP_SET(setlist_name, mSetlistName.c_str(), mSetlistName = _val.Str())
    SYNC_PROP_SET(
        setlist_desc, mSetlistDescription.c_str(), mSetlistDescription = _val.Str()
    )
    SYNC_PROP_SET(setlist_inst, unk50, unk50 = (ScoreType)_val.Int())
    SYNC_PROP_SET(setlist_seconds, unk54 * 86400, unk54 = _val.Int() / 86400)
END_PROPSYNCS