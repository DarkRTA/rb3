#include "meta_band/OvershellPartSelectProvider.h"
#include "meta_band/Utl.h"
#include "game/GameMode.h"
#include "utl/Symbols.h"

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
                if(TheGameMode->Property("allow_coreguitars_with_real", true)->Int(0)){
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

int OvershellPartSelectProvider::NumData() const { return mPartSelections.size(); }

Symbol OvershellPartSelectProvider::DataSymbol(int data) const {
    MILO_ASSERT(( 0) <= (data) && (data) < ( mPartSelections.size()), 0xE5);
    return mPartSelections[data].unk0;
}

void OvershellPartSelectProvider::AddPart(Symbol s, TrackType ty, const char* cc){
    PartSelectEntry entry;
    entry.unk0 = s;
    entry.unk4 = ty;
    entry.unk8 = *cc;
    mPartSelections.push_back(entry);
}