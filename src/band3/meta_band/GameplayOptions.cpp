#include "GameplayOptions.h"
#include "meta/FixedSizeSaveable.h"
#include "meta_band/ProfileMgr.h"
#include "obj/Object.h"
#include "utl/Symbols.h"

GameplayOptions::GameplayOptions() : mVocalVolume(11), mLefty(false), mVocalStyle(kVocStyle1), unk_0x18(false) { mSaveSizeMethod = SaveSize; }

int GameplayOptions::GetVocalVolume(int) const { return mVocalVolume; }

void GameplayOptions::SetVocalVolume(int, int i) {
    if (i < 0 || TheProfileMgr.GetSliderStepCount() <= i) return;
    if (mVocalVolume == i) return;
    unk_0x18 = true;
    mVocalVolume = i;
    
}

void GameplayOptions::SetLefty(bool b) { if (mLefty == b) return; unk_0x18 = true; mLefty = b; }

void GameplayOptions::SetVocalStyle(VocalStyle v) { if (mVocalStyle == v) return; unk_0x18 = true; mVocalStyle = v; }

void GameplayOptions::SaveFixed(FixedSizeSaveableStream& fsss) const {
    GameplayOptions* why = const_cast<GameplayOptions*>(this);
    fsss << mLefty;
    fsss << mVocalVolume;
    fsss << mVocalStyle;
    why->unk_0x18 = false;
}

void GameplayOptions::LoadFixed(FixedSizeSaveableStream& fsss, int) {
    fsss >> mLefty;
    fsss >> mVocalVolume;
    int x;
    fsss >> x;
    mVocalStyle = (VocalStyle)x;
    unk_0x18 = false;
}

int GameplayOptions::SaveSize(int) {
    if (FixedSizeSaveable::sPrintoutsEnabled) TheDebug << MakeString("* %s = %i\n", "GameplayOptions", 9);
    return 9;
}

BEGIN_HANDLERS(GameplayOptions)
    HANDLE_EXPR(get_lefty, GetLefty())
    HANDLE_ACTION(set_lefty, SetLefty(_msg->Int(2)))
    HANDLE_EXPR(get_vocal_style, GetVocalStyle())
    HANDLE_ACTION(set_vocal_style, SetVocalStyle((VocalStyle)_msg->Int(2)))
    HANDLE_EXPR(get_vocal_volume, GetVocalVolume(_msg->Int(2)))
    HANDLE_ACTION(set_vocal_volume, SetVocalVolume(_msg->Int(2), _msg->Int(3)))
    HANDLE_CHECK(117)
END_HANDLERS