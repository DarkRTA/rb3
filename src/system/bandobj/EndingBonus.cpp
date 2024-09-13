#include "bandobj/EndingBonus.h"
#include "utl/Symbols.h"

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
    if(mMiniIcons.size() != 5){
        mMiniIcons.clear();
        for(int i = 0; i < 5; i++){
            mMiniIcons.push_back(MiniIconData(this, Find<UnisonIcon>(MakeString("unison_icon_%d", i), true)));
        }
    }
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