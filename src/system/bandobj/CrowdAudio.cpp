#include "bandobj/CrowdAudio.h"
#include "obj/Task.h"
#include "synth/Sequence.h"
#include "obj/MsgSource.h"
#include "utl/Messages.h"

CrowdAudio* TheCrowdAudio;

void CrowdAudio::Init() { Hmx::Object::RegisterFactory(StaticClassName(), NewObject); }

CrowdAudio::CrowdAudio() : mCurrentMogg(0, 0), mOldMogg(0, 0), mFadingMogg(0, 0), mMainFader(Hmx::Object::New<Fader>()), mWantDuck(0), mResultsDuck(0),
    mResultsFadeDuration(1000.0f), mResultsFader(Hmx::Object::New<Fader>()), unk40(1000.0f), mEntryFader(Hmx::Object::New<Fader>()), unk48(1000.0f), mLevel(kExcitementBad),
    mLoopChangeTime(1e+30f), mIntro(0), mVenueIntro(0), unk64(0), mVenueOutro(0), mState(0), unk70(0), unk74(0), mEnabled(1), mCrowdReacts(1), unk80(0), unk84(1),
    unk88(this, 0), mCurrentBankFader(0), mOtherBankFader(0), mReleaseFader(Hmx::Object::New<Fader>()), unka0(1000.0f), unka4(5000.0f), mPaused(0),
    mShouldPlayVenueIntro(0), mShouldPlayVenueOutro(0), mWon(0), mRestarting(1), mCloseupFader(Hmx::Object::New<Fader>()), mCloseupFadeDuration(1000.0f) {
    mOverrideExcitementLevel = (ExcitementLevel)-1;
    unk54 = -1;
    if(!TheCrowdAudio){
        TheCrowdAudio = this;
        static DataNode& crowd_audio = DataVariable("crowd_audio");
        crowd_audio = DataNode(this);
    }
    mEntryFader->SetMode(Fader::kInvExp);
}

CrowdAudio::~CrowdAudio(){
    if(TheCrowdAudio == this){
        TheCrowdAudio = 0;
        static DataNode& crowd_audio = DataVariable("crowd_audio");
        crowd_audio = DataNode(0);
    }
    StopAllMoggs();
    RELEASE(mMainFader);
    RELEASE(mResultsFader);
    RELEASE(mCurrentBankFader);
    RELEASE(mOtherBankFader);
    RELEASE(mReleaseFader);
    RELEASE(mCloseupFader);
    RELEASE(mEntryFader);
}

void CrowdAudio::Enter(){
    RndPollable::Enter();
    mState = 0;
    mWon = false;
    mLoopChangeTime = 1e+30f;
    unk80 = 0;
    mWantDuck = HandleType(want_outro_duck_msg).Int(0);
    SetEnabled(true);
    SetPaused(false);
}

void CrowdAudio::Exit(){
    RndPollable::Exit();
    SetEnabled(false);
    StopAllMoggs();
    StopSequence("win_4.cue");
    StopSequence("win_5.cue");
    mRestarting = true;
}

void CrowdAudio::Poll(){
    static DataNode& override_crowd_audio_level = DataVariable("override_crowd_audio_level");
    if(override_crowd_audio_level.Int(0)){
        mOverrideExcitementLevel = (ExcitementLevel)override_crowd_audio_level.Int(0);
        if(unk54 != mOverrideExcitementLevel) SetExcitement(mOverrideExcitementLevel);
    }
    else mOverrideExcitementLevel = (ExcitementLevel)-1;
    unk54 = mOverrideExcitementLevel;
    if(mEnabled){
        float secs = TheTaskMgr.Seconds(TaskMgr::a);
        float othersecs = secs * 1000.0f;
        if(secs > mLoopChangeTime) PlayExcitementLoop();
        if(mOldMogg && mReleaseFader->mVal == -96.0f){
            mOldMogg->Stop();
            mOldMogg = 0;
        }
        if(mCurrentMogg && mCurrentMogg->IsStreaming() && mOldMogg && !mReleaseFader->IsFading()){
            mReleaseFader->CancelFade();
            mReleaseFader->SetMode(Fader::kInvExp);
            mReleaseFader->DoFade(-96.0f, unka4);
        }
        if(mFadingMogg && mOtherBankFader->mVal == -96.0f){
            mFadingMogg->Stop();
            mFadingMogg = 0;
        }
        MaybeClap(othersecs);
    }
}

void CrowdAudio::SetPaused(bool b){
    if(b != mPaused){
        if(mState < 4){
            mPaused = b;
            if(mPaused && mOldMogg){
                mOldMogg->Stop();
                mOldMogg = 0;
            }
            if(mCurrentMogg) mCurrentMogg->Pause(mPaused);
            if(mFadingMogg){
                mFadingMogg->Pause(mPaused);
                if(mPaused){
                    mCurrentBankFader->CancelFade();
                    mOtherBankFader->CancelFade();
                    mReleaseFader->CancelFade();
                }
                else {
                    mCurrentBankFader->DoFade(0.0f, unka0);
                    mOtherBankFader->DoFade(-96.0f, unka0);
                    mReleaseFader->DoFade(-96.0f, unka0);
                }
            }
            if(!mPaused) UpdateVolume();
        }
    }
}

void CrowdAudio::SetExcitement(ExcitementLevel level){
    if(mOverrideExcitementLevel != (ExcitementLevel)-1) level = mOverrideExcitementLevel;
    if(level >= kNumExcitements) MILO_FAIL("Invalid excitement level: %d", level);
    if(mState != 2) mLevel = level;
    else {
        static const char* upSfx[5] = { "crowd_upto_poor", "crowd_upto_poor", "crowd_upto_norm", "crowd_upto_good", "crowd_upto_peak" };
        static const char* downSfx[5] = { "crowd_dnto_danger", "crowd_dnto_poor", "crowd_dnto_norm", "crowd_dnto_good", "crowd_dnto_good" };
        PlaySequence(((level > mLevel) ? upSfx : downSfx)[level]);

        mLevel = level;
        mLoopChangeTime = TheTaskMgr.Seconds(TaskMgr::a) + 1.0f;
    }
}

void CrowdAudio::PlayExcitementLoop(){
    mLoopChangeTime = 1e+30f;
    PlayLoop(unk64->Array(mLevel + 1), false);
}

bool CrowdAudio::PlayLoop(const DataArray* loopInfo, bool force){
    MILO_ASSERT(loopInfo != NULL, 0x163);
    BinkClip* clip = 0;
    const char* clipname = loopInfo->Str(1);
    if(unk88){
        clip = unk88->Find<BinkClip>(clipname, false);
        if(!clip){
            MILO_WARN("%s not found in %s_bank.milo", clipname, unk88->Name());
        }
    }
    if(!clip) return false;
    else {
        bool b2 = false;
        if(clip != mCurrentMogg){
            if(clip == mOldMogg){
                if(mCurrentMogg) mCurrentMogg->Stop();
                mOldMogg->RemoveFader(mReleaseFader);
                mCurrentMogg = mOldMogg;
                mOldMogg = 0;
            }
            else b2 = true;
        }
        if(b2 || force){
            if(mCurrentMogg){
                mCurrentMogg->Stop();
            }
            else if(!mOldMogg){
                if(clip == mCurrentMogg){
                    MILO_ASSERT(force, 0x1AA);
                }
                else {
                    mOldMogg = mCurrentMogg;
                    if(mOldMogg){
                        mOldMogg->AddFader(mReleaseFader);
                        mReleaseFader->SetVal(0.0f);
                    }
                }
            }
            mCurrentMogg = clip;
            DataArray* loopArr = loopInfo->Array(2);
            float pan = (loopArr->Float(1) + loopArr->Float(2)) * 0.5f;
            mCurrentMogg->SetPan(0, pan);
            mCurrentMogg->SetPan(1, pan);
            mCurrentMogg->AddFader(mMainFader);
            mCurrentMogg->AddFader(mEntryFader);
            mCurrentMogg->AddFader(mResultsFader);
            mCurrentMogg->AddFader(mCurrentBankFader);
            mCurrentMogg->RemoveFader(mOtherBankFader);
            mCurrentMogg->RemoveFader(mReleaseFader);
            mCurrentMogg->Play();
            SetPaused(mPaused);
        }
        return true;
    }
}

void CrowdAudio::PlaySequence(const char* cc){
    Sequence* seq = 0;
    if(unk88){
        seq = unk88->Find<Sequence>(cc, false);
        if(!seq) MILO_WARN("%s not found in %s_bank.milo", cc, unk88->Name());
    }
    if(seq){
        seq->mFaders.Add(mMainFader);
        seq->mFaders.Add(mEntryFader);
        seq->mFaders.Add(mResultsFader);
        seq->mFaders.Add(mCurrentBankFader);
        seq->mFaders.Remove(mOtherBankFader);
        seq->Play(0,0,0);
    }
}

void CrowdAudio::StopSequence(const char* cc){
    Sequence* seq = 0;
    if(unk88) seq = unk88->Find<Sequence>(cc, false);
    if(seq) seq->Stop(true);
}

void CrowdAudio::PlayCloseupAudio(){
    const char* cue_name = "crowd_closeup.cue";
    Sequence* seq = 0;
    if(unk88) seq = unk88->Find<Sequence>(cue_name, false);
    if(seq){
        seq->Stop(false);
        seq->mFaders.Add(mCloseupFader);
    }
    mCloseupFader->SetVal(0.0f);
    PlaySequence(cue_name);
}

void CrowdAudio::StopCloseupAudio(){
    mCloseupFader->DoFade(-96.0f, mCloseupFadeDuration);
}

void CrowdAudio::UpdateVolume(){
    static DataNode& volumeSetting = DataVariable("crowd_audio.volume");
    float f1 = unk70 + unk74 + volumeSetting.Float(0);
    if(f1 > 3.0f){
        MILO_WARN("Excessive crowd audio volume!\n");
        f1 = 3.0f;
    }
    mMainFader->SetVal(f1);
}

void CrowdAudio::SetEnabled(bool b){
    MsgSource* src = dynamic_cast<MsgSource*>(Dir());
    if(src) src->RemoveSink(this);
    mEnabled = b;
    if(mEnabled){
        if(src) src->AddSink(this);
        SetExcitement(mLevel);
    }
}

void CrowdAudio::StopAllMoggs(){
    if(mCurrentMogg){
        mCurrentMogg->Stop();
        mCurrentMogg = 0;
    }
    if(mOldMogg){
        mOldMogg->Stop();
        mOldMogg = 0;
    }
    if(mFadingMogg){
        mFadingMogg->Stop();
        mFadingMogg = 0;
    }
}

void CrowdAudio::SetTypeDef(DataArray* arr){
    if(TypeDef() != arr){
        Hmx::Object::SetTypeDef(arr);
        mIntro = 0;
        unk64 = 0;
        mVenueIntro = 0;
        mVenueOutro = 0;
        unk78 = 0;
        unk70 = 0;
        unk74 = 0;
        mResultsDuck = 0;
        mResultsFadeDuration = 1000.0f;
        unk48 = 1000.0f;
        mCloseupFadeDuration = 1000.0f;
        unka0 = 1000.0f;
        unka4 = 5000.0f;
        unk40 = 1000.0f;
        if(arr){
            arr->FindData("clap_early_amount_ms", unk78, false);
            arr->FindData("crowd_volume", unk70, false);
            DataArray* streamArr = arr->FindArray("streams", false);
            if(streamArr){
                mIntro = streamArr->FindArray("intro", true);
                unk64 = streamArr->FindArray("levels", true);
                mVenueIntro = streamArr->FindArray("venue_intro", true);
                mVenueOutro = streamArr->FindArray("venue_outro", true);
            }
            arr->FindData("results_duck", mResultsDuck, false);
            arr->FindData("results_fade_ms", mResultsFadeDuration, false);
            arr->FindData("venue_change_fade_ms", unk48, false);
            arr->FindData("closeup_fade_ms", mCloseupFadeDuration, false);
            arr->FindData("crossfade_ms", unka0, false);
            arr->FindData("release_ms", unka4, false);
            arr->FindData("fade_in_from_loading_ms", unk40, false);
        }
        UpdateVolume();
    }
}