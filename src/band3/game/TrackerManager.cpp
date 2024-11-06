#include "game/TrackerManager.h"
#include "TrackerDisplay.h"
#include "bandtrack/TrackPanel.h"
#include "game/TrackerSource.h"
#include "meta_band/ProfileMgr.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "utl/Symbol.h"

TrackerManager::TrackerManager(Band* band) : unk0(-1), unk4(0), mBandDisplayType(kTrackerBandDisplay_Graphic), mBandDisplayStyle((TrackerBandDisplayStyle)0), mBand(band), mTracker(0), unk48(1), unk49(0), unk4c(-1.0f) {

}

TrackerManager::~TrackerManager(){
    RELEASE(mTracker);
}

void TrackerManager::ForceStars(int stars){
    unk0 = stars;
}

void TrackerManager::Restart(){
    unk48 = true;
    unk49 = false;
    unk4c = -1.0f;
    if(mTracker){
        TrackerSource* src = CreateSource(mDesc);
        if(src){
            mTracker->UpdateSource(src);
        }
        mTracker->Restart();
    }
}

void TrackerManager::HandleAddPlayer(Player* p){
    if(mTracker) mTracker->HandleAddPlayer(p);
}

void TrackerManager::HandleRemovePlayer(Player* p){
    if(mTracker) mTracker->HandleRemovePlayer(p);
}

void TrackerManager::HandleGameOver(float f){
    if(mTracker) mTracker->HandleGameOver(f);
}

void TrackerManager::StartIntro(){
    Quest* q = TheTour->GetQuest();
    if(q){
        mTracker->unk48 = q->GetDescription();
        mTracker->unk4c = q->GetDisplayName();
    }
    if(mTracker) mTracker->StartIntro();
}

void TrackerManager::Poll(float f){
    if(mTracker){
        if(unk48){
            mBandDisplay.SetType(mBandDisplayType);
            mBandDisplay.SetStyle(mBandDisplayStyle);
            unk48 = 0;
        }
        int level = mTracker->GetTargetSuccessLevel();
        mTracker->Poll(f + unk4);
        if(mBandDisplayType == (TrackerBandDisplayType)0){
            float prog = mTracker->CalcProgressPercentage();
            if(prog != unk4c){
                mBandDisplay.SetProgressPercentage(prog);
                if(prog > 0 && prog > unk4c){
                    GetTrackPanel()->PlaySequence("successful_contribution.cue", 0, 0, 0);
                }
                unk4c = prog;
            }
        }
        int newlevel = mTracker->GetTargetSuccessLevel();
        if(level != newlevel) mTracker->ReachedTargetLevel(newlevel);
        if(!unk49 && mBand){
            Performer* perf = mBand->GetBand();
            if(perf->unk1e1){
                HandleGameOver(f);
                unk49 = true;
            }
        }
    }
}

void TrackerManager::ConfigureGoals(){
    for(int i = 0; i < 4; i++){
        float offset = TheProfileMgr.GetSyncOffset(i);
        if(i == 0) unk4 = offset;
        else if(offset < unk4){
            unk4 = offset;
        }
    }
    unk0 = -1;
    MILO_ASSERT(mBand, 0xEA);
    ConfigureQuestGoal();
    ConfigureAccomplishmentGoal();
    if(!mTracker){
        GetTrackPanel()->SetMainGoalConfiguration(TrackPanel::kConfigScoreStars);
        GetTrackPanel()->ShowMainGoalInfo(false);
    }
}

void TrackerManager::ConfigureQuestGoal(){

}