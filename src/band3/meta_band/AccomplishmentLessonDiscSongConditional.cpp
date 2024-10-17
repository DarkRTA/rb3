#include "meta_band/AccomplishmentLessonDiscSongConditional.h"
#include "AccomplishmentConditional.h"
#include "AccomplishmentDiscSongConditional.h"
#include "game/Defines.h"
#include "meta_band/Accomplishment.h"
#include "meta_band/BandSongMgr.h"
#include "obj/Data.h"
#include "os/Debug.h"
#include "utl/Symbols3.h"

AccomplishmentLessonDiscSongConditional::AccomplishmentLessonDiscSongConditional(DataArray* arr, int i) : AccomplishmentDiscSongConditional(arr, i) {
    Configure(arr);
}

AccomplishmentLessonDiscSongConditional::~AccomplishmentLessonDiscSongConditional(){

}

void AccomplishmentLessonDiscSongConditional::Configure(DataArray* i_pConfig){
    MILO_ASSERT(i_pConfig, 0x1E);
}

AccomplishmentType AccomplishmentLessonDiscSongConditional::GetType() const { return kAccomplishmentTypeLessonDiscSongConditional; }

bool AccomplishmentLessonDiscSongConditional::CheckLessonCompleteCondition(SongStatusMgr* mgr, Symbol s, const AccomplishmentCondition& cond) const {
    if(!TheSongMgr->HasSong(s, false)){
        MILO_WARN("Song: %s not available.  Dynamic Prereqs are probably missing!", s.Str());
        return false;
    }
    else {
        int songid = TheSongMgr->GetSongIDFromShortName(s, true);
        ScoreType ty = cond.mScoreType;
        switch(ty){
            case kScoreRealGuitar:
                return mgr->IsProGuitarSongLessonComplete(songid, cond.mDifficulty);
            case kScoreRealBass:
                return mgr->IsProBassSongLessonComplete(songid, cond.mDifficulty);
            case kScoreRealKeys:
                return mgr->IsProKeyboardSongLessonComplete(songid, cond.mDifficulty);
            default:
                MILO_WARN("CheckLessonCompleteCondition is not currently supported with score type: %i \n", ty);
                return false;
        }
    }
}

bool AccomplishmentLessonDiscSongConditional::CheckConditionsForSong(SongStatusMgr* mgr, Symbol s) const {
    for(std::vector<AccomplishmentCondition>::const_iterator it = m_lConditions.begin(); it != m_lConditions.end(); ++it){
        const AccomplishmentCondition& cond = *it;
        Symbol condsym = cond.mCondition;
        if(condsym == lesson_complete){
            if(CheckLessonCompleteCondition(mgr, s, cond)) return true;
        }
        else {
            MILO_WARN("GOAL: %s - Condition is not currently supported: %s \n", mName, condsym);
            return false;
        }
    }
    return false;
}