#include "game/TrackerManager.h"
#include "FocusTracker.h"
#include "PerfectSectionTracker.h"
#include "StatMemberTracker.h"
#include "Tracker.h"
#include "TrackerDisplay.h"
#include "bandtrack/TrackPanel.h"
#include "game/AccuracyTracker.h"
#include "game/BandUser.h"
#include "game/DeployCountTracker.h"
#include "game/OverdriveTimeTracker.h"
#include "game/OverdriveTracker.h"
#include "game/PerfectOverdriveTracker.h"
#include "game/ScoreTracker.h"
#include "game/StreakTracker.h"
#include "game/TrackerSource.h"
#include "meta_band/AccomplishmentManager.h"
#include "meta_band/BandProfile.h"
#include "meta_band/Campaign.h"
#include "meta_band/ProfileMgr.h"
#include "os/Debug.h"
#include "tour/Tour.h"
#include "tour/TourDesc.h"
#include "tour/TourQuestGameRules.h"
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
    Quest* q = TheTour->GetQuest();
    if(q){
        mBandDisplayType = kTrackerBandDisplay_Graphic;
        mBandDisplayStyle = (TrackerBandDisplayStyle)0;
        const TourQuestGameRules* rules = q->GetGameRules();
        TrackerDesc desc;
        TrackerType ty = GetTrackerTypeFromGameType(rules->GetGameType());
        if(ty == 0) return;
        else {
            desc.mType = ty;
            desc.unkc = TrackPanel::kConfigStarsGoal;
            desc.unk10 = true;
            desc.unk11 = true;
            desc.unk12 = true;
            for(int i = 0; i < rules->GetNumTargets(); i++){
                float target = rules->GetTarget(i);
                desc.unk18.push_back(target);
            }
            desc.unk20 = true;
            desc.unk24 = rules->GetChallengeSpecificData();
            SetTracker(desc);
        }
    }
}

void TrackerManager::ConfigureAccomplishmentGoal(){
    if(TheCampaign){
        BandProfile* campaignprofile = TheCampaign->GetProfile();
        BandProfile* primaryprofile = TheProfileMgr.GetPrimaryProfile();
        if(primaryprofile == campaignprofile && !mTracker){
            Symbol goal = TheCampaign->GetCurrentGoal();
            MILO_ASSERT(TheAccomplishmentMgr, 0x15E);
            Accomplishment* acc = TheAccomplishmentMgr->GetAccomplishment(goal);
            if(acc){
                mBandDisplayType = kTrackerBandDisplay_Text;
                mBandDisplayStyle = (TrackerBandDisplayStyle)1;
                TrackerDesc desc;
                acc->InitializeTrackerDesc(desc);
                if(desc.mType != kTrackerType_Undef){
                    SetTracker(desc);
                }
            }
        }
    }
}

int TrackerManager::GetQuestEarnedStars() const {
    if(mTracker){
        if(unk0 != -1) return unk0;
        else {
            MILO_ASSERT(mBand, 0x18B);
            return std::floor(mBand->GetBand()->mStats.unk1c4 * 5.0f);
        }
    }
    else return 0;
}

void TrackerManager::UpdateQuestGoalLabel(UILabel* label) const {
    MILO_ASSERT(label, 0x19C);
    if(mTracker){
        mTracker->UpdateGoalValueLabel(*label);
    }
}

void TrackerManager::UpdateQuestResultLabel(UILabel* label) const {
    MILO_ASSERT(label, 0x1A9);
    if(mTracker){
        mTracker->UpdateCurrentValueLabel(*label);
    }
}

String TrackerManager::GetPlayerContributionString(Symbol s) const {
    if(mTracker){
        if(mTracker->HasPlayerForInstrument(s)){
            return mTracker->GetPlayerContributionString(s);
        }
    }
    return "";
}

void TrackerManager::OnStatsSynced(){
    if(mTracker) mTracker->ReconcileStats();
}

void TrackerManager::OnPlayerAddEnergy(Player* p, float f){
    if(mTracker){
        FocusTracker* ft = dynamic_cast<FocusTracker*>(mTracker);
        if(ft) ft->PlayerAddEnergy(p, f);
    }
}

void TrackerManager::OnPlayerSaved(Player* p){
    if(mTracker) mTracker->HandlePlayerSaved(p);
}

void TrackerManager::OnPlayerQuarantined(Player* p){
    HandleRemovePlayer(p);
}

void TrackerManager::OnRemoteTrackerFocus(Player* p, int i1, int i2, int i3){
    if(mTracker){
        FocusTracker* ft = dynamic_cast<FocusTracker*>(mTracker);
        if(!ft) MILO_FAIL("Non-focus tracker sent focus related net message!");
        ft->RemoteSetFocusPlayer(p, i1, i2, (FocusTracker::FocusFlags)i3);
    }
}

void TrackerManager::OnRemoteTrackerPlayerProgress(Player* p, float f){
    if(mTracker) mTracker->RemoteSetPlayerProgress(p, f);
}

void TrackerManager::OnRemoteTrackerSectionComplete(Player* p, int i1, int i2, int i3){
    if(mTracker){
        PerfectSectionTracker* pst = dynamic_cast<PerfectSectionTracker*>(mTracker);
        if(!pst) MILO_FAIL("Non-perfect-section tracker sent perfect-section related net message!");
        pst->RemoteSectionComplete(p, i1, i2, i3);
    }
}

void TrackerManager::OnRemoteTrackerPlayerDisplay(Player* p, int i1, int i2, int i3){
    if(mTracker) mTracker->RemoteTrackerPlayerDisplay(p, i1, i2, i3);
}

void TrackerManager::OnRemoteTrackerDeploy(Player* p){
    if(mTracker){
        DeployCountTracker* dct = dynamic_cast<DeployCountTracker*>(mTracker);
        if(!dct) MILO_FAIL("Non-deploy tracker sent deploy related net message!");
        dct->RemoteDeploy(p);
    }
}

void TrackerManager::OnRemoteTrackerEndDeployStreak(Player* p, int i){
    if(mTracker){
        OverdriveTracker* ot = dynamic_cast<OverdriveTracker*>(mTracker);
        if(!ot) MILO_FAIL("Non-overdrive tracker sent overdrive related net message!");
        ot->RemoteEndDeployStreak(p, i);
    }
}

void TrackerManager::OnRemoteTrackerEndStreak(Player* p, int i1, int i2){
    if(mTracker) mTracker->RemoteEndStreak(p, i1, i2);
}

TrackerSource* TrackerManager::CreateSource(const TrackerDesc& desc) const {
    LocalBandUser* pUser = desc.mUser;
    if(!pUser) return new BandTrackerSource(mBand);
    MILO_ASSERT(pUser, 600);
    Player* p = pUser->GetPlayer();
    if(!p){
        MILO_WARN("Couldn't make tracker for type %d. No player for user.", desc.mType);
        return nullptr;
    }
    else return new PlayerTrackerSource(p);
}

void TrackerManager::SetTracker(const TrackerDesc& desc){
    TrackerSource* src = CreateSource(desc);
    if(src){
        Tracker* tracker = MakeTracker(desc.mType, src);
        if(!tracker){
            MILO_WARN("Couldn't create tracker for type %d", desc.mType);
        }
        else {
            tracker->Configure(desc);
            if(mTracker){
                MILO_FAIL("Only one tracker at a time!");
            }
            mTracker = tracker;
            GetTrackPanel()->SetMainGoalConfiguration(desc.unkc);
            GetTrackPanel()->SetSuppressUnisonDisplay(desc.unk10);
            mDesc = desc;
        }
    }
}

Tracker* TrackerManager::MakeTracker(TrackerType ty, TrackerSource* src){
    Tracker* tracker = nullptr;
    switch(ty){
        case kTrackerType_Accuracy:
            tracker = new AccuracyTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_AccuracyFocus:
            tracker = new AccuracyFocusTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_CareerDeployCount:
            tracker = new DeployStatMemberTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_CareerFills:
            tracker = new FillsHitStatMemberTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_HopoCount:
            tracker = new HopoStatMemberTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_HopoPercent:
            tracker = new HopoPercentStatMemberTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_Overdrive:
            tracker = new OverdriveTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_OverdriveDeployCount:
            tracker = new DeployStatMemberTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_OverdriveTime:
            tracker = new OverdriveTimeTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_PerfectOverdrive:
            tracker = new PerfectOverdriveTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_PerfectSection:
            tracker = new PerfectSectionTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_Score:
            tracker = new ScoreTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_SoloButtonedSoloPercentage:
            tracker = new SoloButtonedSoloStatMemberTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_Streak:
            tracker = new StreakTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_StreakCount:
            tracker = new StreakCountStatMemberTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_StreakFocus:
            tracker = new StreakFocusTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_DeployCount:
            tracker = new DeployCountTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_UnisonCount:
            tracker = new UnisonStatMemberTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_UpstrumCount:
            tracker = new UpstrumStatMemberTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        case kTrackerType_UpstrumPercent:
            tracker = new UpstrumPercentStatMemberTracker(src, mBandDisplay, mBroadcastDisplay);
            break;
        default:
            break;
    }
    return tracker;
}

TrackerType TrackerManager::GetTrackerTypeFromGameType(TourGameType ty) const {
    switch(ty){
        case 1:
            return kTrackerType_Accuracy;
        case 2:
            return kTrackerType_AccuracyFocus;
        case 3:
            return kTrackerType_DeployCount;
        case 4:
            return kTrackerType_HopoCount;
        case 6:
            return kTrackerType_Overdrive;
        case 9:
            return kTrackerType_PerfectOverdrive;
        case 10:
            return kTrackerType_PerfectSection;
        case 7:
            return kTrackerType_Streak;
        case 8:
            return kTrackerType_StreakFocus;
        case 11:
            return kTrackerType_UnisonCount;
        case 12:
            return kTrackerType_UpstrumCount;
        default:
            return kTrackerType_Undef;
    }
}