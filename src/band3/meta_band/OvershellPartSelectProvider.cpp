#include "meta_band/OvershellPartSelectProvider.h"
#include "beatmatch/TrackType.h"
#include "game/BandUser.h"
#include "game/Defines.h"
#include "meta_band/Campaign.h"
#include "meta_band/OvershellSlot.h"
#include "meta_band/OvershellSlotState.h"
#include "meta_band/Utl.h"
#include "game/GameMode.h"
#include "os/Debug.h"
#include "os/Joypad.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

OvershellPartSelectProvider::OvershellPartSelectProvider(OvershellPanel* panel) : mControllerType(kControllerNone), mUser(0), mOvershell(panel) {

}

OvershellPartSelectProvider::~OvershellPartSelectProvider(){
    Clear();
}

void OvershellPartSelectProvider::Reload(ControllerType ty, BandUser* user){
    Clear();
    mControllerType = ty;
    mUser = user;
    switch(ty){
        case kControllerDrum:
            AddPart(overshell_drums, kTrackDrum, GetFontCharFromTrackType(kTrackDrum, 0));
            AddPart(overshell_drums_pro, kTrackDrum, GetFontCharForProDrums(0));
            break;
        case kControllerGuitar:
            AddPart(overshell_guitar, kTrackGuitar, GetFontCharFromTrackType(kTrackGuitar, 0));
            AddPart(overshell_bass, kTrackBass, GetFontCharFromTrackType(kTrackBass, 0));
            if(mOvershell->CanGuitarPlayKeys()){
                AddPart(overshell_keys, kTrackKeys, GetFontCharFromTrackType(kTrackKeys, 0));
            }
            break;
        case kControllerVocals:
            AddPart(overshell_vocal_solo, kTrackVocals, GetFontCharFromTrackType(kTrackVocals, 0));
            AddPart(overshell_vocal_harmony, kTrackVocals, GetFontCharForHarmonyMics(2, 0));
            break;
        case kControllerKeys:
            AddPart(overshell_keys, kTrackKeys, GetFontCharFromTrackType(kTrackKeys, 0));
            AddPart(overshell_real_keys, kTrackRealKeys, GetFontCharFromTrackType(kTrackRealKeys, 0));
            AddPart(overshell_guitar, kTrackGuitar, GetFontCharFromTrackType(kTrackGuitar, 0));
            AddPart(overshell_bass, kTrackBass, GetFontCharFromTrackType(kTrackBass, 0));
            break;
        case kControllerRealGuitar:
            AddPart(overshell_real_guitar, kTrackRealGuitar, GetFontCharFromTrackType(kTrackRealGuitar, 0));
            AddPart(overshell_real_bass, kTrackRealBass, GetFontCharFromTrackType(kTrackRealBass, 0));
            if(mUser->mHasButtonGuitar){
                if(TheGameMode->Property("allow_coreguitars_with_real", true)->Int()){
                    AddPart(overshell_guitar, kTrackGuitar, GetFontCharFromTrackType(kTrackGuitar, 0));
                    AddPart(overshell_bass, kTrackBass, GetFontCharFromTrackType(kTrackBass, 0));
                }
            }
            break;
        default:
            break;
    }
}

void OvershellPartSelectProvider::Clear(){
    mPartSelections.clear();
}

bool OvershellPartSelectProvider::IsActive(int data) const {
    if(mPartSelections.empty()) return false;
    if(!mUser->IsParticipating()) return true;
    MILO_ASSERT_RANGE(data, 0, mPartSelections.size(), 0x6E);
    const PartSelectEntry& entry = mPartSelections[data];
    if(mUser->IsLocal() && entry.unk0 == overshell_drums_pro){
        if(UserHasGHDrums(mUser->GetLocalUser())) return false;
    }
    if(mUser->GetTrackType() != kTrackNone && mUser->GetTrackType() != kTrackPending && 
        mUser->GetTrackType() != kTrackPendingVocals && mUser->GetTrackType() != entry.unk4){
        return false;
    }

    for(int i = 0; i < (int)mOvershell->mSlots.size(); i++){
        OvershellSlot* curslot = mOvershell->GetSlot(i);
        BandUser* curuser = curslot->GetUser();
        if(curuser && curuser != mUser){
            OvershellSlotState* curstate = curslot->GetState();
            if(!curstate->IsPartUnresolved()){
                if(RepresentSamePart(entry.unk4, curuser->GetTrackType())) return false;
            }
        }
    }

    if(TheGameMode->InMode("campaign") || TheGameMode->InMode("pro_song_lessons_keyboard") ||
        TheGameMode->InMode("pro_song_lessons_real_guitar") || TheGameMode->InMode("pro_song_lessons_real_bass")){

        TrackType reqTrackType = TheCampaign->GetRequiredTrackTypeForCurrentAccomplishment();
        ScoreType reqScoreType = TheCampaign->GetRequiredScoreTypeForCurrentAccomplishment();

        if(reqTrackType == kTrackNone) return true;
        if(!TheCampaign->GetLaunchUser()) return true;
        if(TheCampaign->GetLaunchUser() == mUser){
            if(entry.unk4 != reqTrackType) return false;
            if(reqScoreType == 6 && entry.unk0 != "overshell_drums_pro") return false;
            if(reqScoreType == 0 && entry.unk0 != "overshell_drums") return false;
            if(reqScoreType == 3 && entry.unk0 != "overshell_vocal_solo") return false;
            if(reqScoreType == 4 && entry.unk0 != "overshell_vocal_harmony") return false;
        }
        else if(RepresentSamePart(entry.unk4, reqTrackType)) return false;

    }
    return true;
}

int OvershellPartSelectProvider::NumData() const { return mPartSelections.size(); }

Symbol OvershellPartSelectProvider::DataSymbol(int data) const {
    MILO_ASSERT_RANGE(data, 0, mPartSelections.size(), 0xE5);
    return mPartSelections[data].unk0;
}

void OvershellPartSelectProvider::AddPart(Symbol s, TrackType ty, const char* cc){
    PartSelectEntry entry;
    entry.unk0 = s;
    entry.unk4 = ty;
    entry.unk8 = *cc;
    mPartSelections.push_back(entry);
}
