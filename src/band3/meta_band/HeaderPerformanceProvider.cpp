#include "meta_band/HeaderPerformanceProvider.h"
#include "bandobj/ScoreDisplay.h"
#include "game/Defines.h"
#include "meta_band/AppLabel.h"
#include "meta_band/BandSongMgr.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "ui/UIEnums.h"
#include "ui/UIListCustom.h"
#include "ui/UIListLabel.h"
#include "utl/Symbol.h"
#include "utl/Symbols.h"
#include "utl/Symbols4.h"

SetlistScoresProvider::SetlistScoresProvider() : mProfile(0), mScoreType(kNumScoreTypes) {

}

void SetlistScoresProvider::Custom(int, int data, UIListCustom* slot, Hmx::Object* obj) const {
    if(slot->Matches("score")){
        ScoreDisplay* sd = dynamic_cast<ScoreDisplay*>(obj);
        MILO_ASSERT(sd, 0x23);
        short val;
        if(mScoreType == kScoreBand){
            val = unk30[data];
        }
        else {
            val = 1 << mScoreType;
        }
        sd->SetValues(val, unk28[data], 0, false);
        sd->SetShowing(true);
    }
}

void SetlistScoresProvider::Text(int, int data, UIListLabel* slot, UILabel* label) const {
    if(slot->Matches("song")){
        AppLabel* appLabel = dynamic_cast<AppLabel*>(label);
        MILO_ASSERT(appLabel, 0x37);
        appLabel->SetSongNameWithNumber(unk20[data], data + 1, unk38[data].empty() ? 0 : unk38[data].c_str());
    }
    else label->SetTextToken(gNullStr);
}

UIListWidgetState SetlistScoresProvider::ElementStateOverride(int, int data, UIListWidgetState state) const {
    bool hassong = TheSongMgr->HasSong(unk20[data]);
    UIListWidgetState ret = kUIListWidgetInactive;
    if(hassong) ret = state;
    return ret;
}

int SetlistScoresProvider::NumData() const { return unk20.size(); }

void SetlistScoresProvider::SetProfile(BandProfile* profile){
    MILO_ASSERT(profile, 0x65);
    mProfile = profile;
}

void SetlistScoresProvider::SetScoreType(ScoreType type){ mScoreType = type; }

BEGIN_HANDLERS(SetlistScoresProvider)
    HANDLE_ACTION(set_score_type, SetScoreType(SymToScoreType(_msg->Sym(2))))
    HANDLE_ACTION(set_profile, SetProfile(_msg->Obj<BandProfile>(2)))
    HANDLE_ACTION(refresh_scores, RefreshScores())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x87)
END_HANDLERS