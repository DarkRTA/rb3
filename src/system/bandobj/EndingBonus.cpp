#include "bandobj/EndingBonus.h"
#include "utl/Symbols.h"
#include "utl/Messages.h"

EndingBonus::EndingBonus() : mSuppressUnisonDisplay(0), unk18d(0), mScore(0), mSucceeded(0), unk198(this, 0), mScoreLabel(this, 0), mUnisonStartTrig(this, 0),
    mUnisonEndTrig(this, 0), mUnisonSucceedTrig(this, 0), mStartTrig(this, 0), mEndTrig(this, 0), mSucceedTrig(this, 0), mResetTrig(this, 0) {

}

void EndingBonus::SyncObjects(){
    RndDir::SyncObjects();
    if(!mScoreLabel) mScoreLabel = Find<BandLabel>("score.lbl", false);
    if(!mUnisonStartTrig) mUnisonStartTrig = Find<EventTrigger>("unison_start.trig", false);
    if(!mUnisonEndTrig) mUnisonEndTrig = Find<EventTrigger>("unison_end.trig", false);
    if(!mUnisonSucceedTrig) mUnisonSucceedTrig = Find<EventTrigger>("unison_succeed.trig", false);
    if(!mStartTrig) mStartTrig = Find<EventTrigger>("start.trig", false);
    if(!mEndTrig) mEndTrig = Find<EventTrigger>("end.trig", false);
    if(!mSucceedTrig) mSucceedTrig = Find<EventTrigger>("succeed.trig", false);
    if(!mResetTrig) mResetTrig = Find<EventTrigger>("reset.trig", false);
    if(mIconData.size() != 5){
        mIconData.clear();
        for(int i = 0; i < 5; i++){
            mIconData.push_back(MiniIconData(this, Find<UnisonIcon>(MakeString("unison_icon_%d", i), true)));
        }
    }
}

void EndingBonus::Start(bool b){
    Reset();
    mSucceeded = false;
    mStartTrig->Trigger();
    SetupEnding(b);
    mScore = 0;
    mScoreLabel->SetInt(0, false);
    unk18d = false;
}

void EndingBonus::MiniIconData::Reset(){
    mFailed = false;
    mSucceeded = false;
    SetUsed(false);
    mIcon->Reset();
}

void EndingBonus::MiniIconData::SetUsed(bool used){
    mUsed = used;
    mIcon->SetShowing(used);
    if(used) mIcon->UnisonStart();
    else mIcon->UnisonEnd();
}

void EndingBonus::MiniIconData::Succeeded(){
    if(!mSucceeded){
        mIcon->Succeed();
        mSucceeded = true;
    }
}

void EndingBonus::MiniIconData::Failed(){
    if(!mFailed){
        mIcon->Fail();
        mFailed = true;
    }
}

void EndingBonus::MiniIconData::SetProgress(float f){
    if(!mFailed) mIcon->SetProgress(f);
}

void EndingBonus::Reset(){
    mResetTrig->Trigger();
    for(int i = 0; i < mIconData.size(); i++){
        mIconData[i].Reset();
    }
    unk18d = false;
}

void EndingBonus::SetIconText(int slot_index, const char* cc){
    MILO_ASSERT(( 0) <= (slot_index) && (slot_index) < ( mIconData.size()), 0x81);
    mIconData[slot_index].mIcon->SetIcon(cc);
}

void EndingBonus::Success(){
    mSucceeded = true;
    if(mSucceedTrig) mSucceedTrig->Trigger();
    else MILO_WARN("EndingBonus::Success(): 'succeed.trig' not found!");
}

void EndingBonus::PlayerSuccess(int slot_index){
    MILO_ASSERT(( 0) <= (slot_index) && (slot_index) < ( mIconData.size()), 0x90);
    mIconData[slot_index].Succeeded();
}

void EndingBonus::PlayerFailure(int slot_index){
    MILO_ASSERT(( 0) <= (slot_index) && (slot_index) < ( mIconData.size()), 0x96);
    mIconData[slot_index].Failed();
}

void EndingBonus::CodaEnd(){
    unk198 = new MessageTask(this, coda_end_script_msg);
    TheTaskMgr.Start(unk198, kTaskSeconds, 2.0f);
}

void EndingBonus::SetSuppressUnisonDisplay(bool b){ mSuppressUnisonDisplay = b; }

void EndingBonus::UnisonStart(int i){
    if(!unk18d){
        Reset();
        if(!mSuppressUnisonDisplay) mUnisonStartTrig->Trigger();
        SetupUnison(i);
        unk18d = true;
    }
}

void EndingBonus::UnisonEnd(){
    if(unk18d){
        if(!mSuppressUnisonDisplay) mUnisonEndTrig->Trigger();
        unk18d = false;
    }
}

void EndingBonus::UnisonSucceed(){
    if(!mSuppressUnisonDisplay){
        mUnisonSucceedTrig->Trigger();
        for(int i = 0; i < mIconData.size(); i++){
            PlayerSuccess(i);
        }
    }
    unk18d = false;
}

void EndingBonus::SetScore(int score){
    if(mSucceeded) return;
    if(!TheLoadMgr.EditMode() && score == mScore) return;
    mScore = score;
    mScoreLabel->SetInt(score, false);
}

void EndingBonus::SetupEnding(bool b){
    SetIconOrder(-1, b);
}

void EndingBonus::SetupUnison(int i){
    SetIconOrder(i, false);
}

void EndingBonus::DisablePlayer(int slot_index){
    MILO_ASSERT(slot_index < mIconData.size(), 0x105);
    mIconData[slot_index].mDisabled = true;
}

void EndingBonus::EnablePlayer(int slot_index){
    MILO_ASSERT(slot_index < mIconData.size(), 0x10B);
    mIconData[slot_index].mDisabled = false;
}

void EndingBonus::SetProgress(int slot_index, float f){
    MILO_ASSERT(slot_index < mIconData.size(), 0x111);
    mIconData[slot_index].SetProgress(f);
}

BEGIN_HANDLERS(EndingBonus)
    HANDLE_ACTION(coda_end_script, if(!mSucceeded) Find<EventTrigger>("failure.trig", true)->Trigger(); )
    HANDLE_ACTION(start, Start(true))
    HANDLE(reset, OnReset)
    HANDLE_ACTION(success, Success())
    HANDLE_ACTION(coda_end, CodaEnd())
    HANDLE_ACTION(set_score, SetScore(_msg->Int(2)))
    HANDLE_ACTION(unison_end, UnisonEnd())
    HANDLE_ACTION(unison_succeed, UnisonSucceed())
    HANDLE_SUPERCLASS(RndDir)
    HANDLE_CHECK(0x128)
END_HANDLERS

BEGIN_PROPSYNCS(EndingBonus)
    SYNC_PROP(score, mScore)
    SYNC_SUPERCLASS(RndDir)
END_PROPSYNCS

void EndingBonus::Save(BinStream& bs){ RndDir::Save(bs); }
void EndingBonus::PreLoad(BinStream& bs){ RndDir::PreLoad(bs); }
void EndingBonus::PostLoad(BinStream& bs){ RndDir::PostLoad(bs); }

BEGIN_COPYS(EndingBonus)
    COPY_SUPERCLASS(RndDir)
END_COPYS

DataNode EndingBonus::OnReset(DataArray*){
    Reset();
    return DataNode(0);
}