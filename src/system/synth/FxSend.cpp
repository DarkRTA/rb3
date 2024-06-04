#include "synth/FxSend.h"
#include "synth/Sfx.h"
#include "utl/Loader.h"
#include "math/Decibels.h"
#include "synth/Synth.h"
#include "utl/Symbols.h"

INIT_REVS(FxSend);

FxSend::FxSend() : mNextSend(this, 0), mStage(0), mBypass(0), mDryGain(-96.0f), mWetGain(0.0f), 
    mInputGain(0.0f), mReverbMixDb(-96.0f), mReverbEnable(0), mEnableUpdates(1), mChannels(kSendAll) {
}

FxSend::~FxSend(){
    
}

void FxSend::Replace(Hmx::Object* from, Hmx::Object* to){
    Hmx::Object::Replace(from, to);
    MILO_ASSERT(from == mNextSend, 0x30);
    mNextSend = ObjOwnerPtr<FxSend, class ObjectDir>(to, 0);
    RebuildChain();
}

void FxSend::SetNextSend(FxSend* next){
    if(next != mNextSend.Ptr() && CheckChain(next, mStage)){
        mNextSend = next;
        RebuildChain();
    }
}

void FxSend::SetStage(int stage){
    if(stage != mStage && CheckChain(mNextSend, stage)){
        mStage = stage;
        RebuildChain();
    }
}

void FxSend::SetChannels(SendChannels chans){
    if(chans == mChannels) return;
    mChannels = chans;
    RebuildChain();
}

void FxSend::RebuildChain(){
    std::vector<FxSend*> vec;
    BuildChainVector(vec);
    Recreate(vec);
}

void FxSend::BuildChainVector(std::vector<FxSend*>& vec){
    vec.push_back(this);
    std::vector<ObjRef*>::const_reverse_iterator rit = Refs().rbegin();
    std::vector<ObjRef*>::const_reverse_iterator ritEnd = Refs().rend();
    for(; rit != ritEnd; ++rit){
        ObjRef* ref = *rit;
        FxSend* rsend = dynamic_cast<FxSend*>(ref->RefOwner());
        if(rsend && rsend->mNextSend == this) {
            rsend->BuildChainVector(vec);
        }
        else {
            Sfx* seq = dynamic_cast<Sfx*>(ref->RefOwner());
            if(seq) seq->Stop(false);
        }
    }
}

bool FxSend::CheckChain(FxSend* send, int i){
    FxSend* cur;
    for(cur = send; cur && cur != this; cur = cur->mNextSend);
    if(cur == this){
        MILO_WARN("Error: can't have loops in your FX chain.");
        return false;
    }
    else if(send && send->mStage <= i){
        MILO_WARN("Error: output send must be set to a higher stage (%d <= %d).", send->mStage, i);
        return false;
    }
    else {
        std::vector<ObjRef*>::const_reverse_iterator rit = Refs().rbegin();
        std::vector<ObjRef*>::const_reverse_iterator ritEnd = Refs().rend();
        for(; rit != ritEnd; ++rit){
            FxSend* rsend = dynamic_cast<FxSend*>((*rit)->RefOwner());
            if(rsend && rsend->mNextSend == this && rsend->mStage >= i){
                MILO_WARN("Error: stage must be higher than all input sends' stages (see %s).", rsend->Name());
                return false;
            }
        }
        return true;
    }
}

void FxSend::Save(BinStream&){
    MILO_ASSERT(0, 0xA2);
}

void FxSend::Load(BinStream& bs){
    LOAD_REVS(bs);
    ASSERT_REVS(7, 0);
    Hmx::Object::Load(bs);
    FxSend* oldPtr = mNextSend;
    int oldStage = mStage;
    SendChannels oldchans = mChannels;
    bs >> mNextSend;
    bs >> mStage;
    if(gRev < 5){
        if(gRev >= 2){
            float f;
            bs >> f;
            mDryGain = RatioToDb((100.0f - f) / 100.0f);
            mWetGain = RatioToDb(f / 100.0f);
        }
        if(gRev >= 3){
            bs >> mBypass;
        }
    }
    if(gRev >= 4){
        int chans;
        bs >> chans;
        mChannels = (SendChannels)chans;
    }
    if(gRev >= 5){
        bs >> mDryGain >> mWetGain >> mInputGain;
    }
    if(gRev >= 6){
        bs >> mBypass;
    }
    if(gRev >= 7){
        bs >> mReverbMixDb >> mReverbEnable;
    }
    if(mNextSend != oldPtr || mStage != oldStage || mChannels != oldchans) RebuildChain();
    UpdateMix();
}

BEGIN_COPYS(FxSend)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(FxSend)
    BEGIN_COPYING_MEMBERS
        COPY_MEMBER(mNextSend)
        COPY_MEMBER(mStage)
        COPY_MEMBER(mWetGain)
        COPY_MEMBER(mDryGain)
        COPY_MEMBER(mInputGain)
        COPY_MEMBER(mChannels)
        COPY_MEMBER(mBypass)
        COPY_MEMBER(mReverbMixDb)
        COPY_MEMBER(mReverbEnable)
    END_COPYING_MEMBERS
END_COPYS

void FxSend::TestWithMic(){
    MILO_ASSERT(TheLoadMgr.EditMode(), 0x10A);
    Mic* mic = TheSynth->GetMic(0);
    mic->Start();
    mic->StartPlayback();
    mic->SetFxSend(this);
}

void FxSend::EnableUpdates(bool b){
    mEnableUpdates = b;
    if(!b) return;
    OnParametersChanged();
}

BEGIN_HANDLERS(FxSend)
    HANDLE_ACTION(test_with_mic, TestWithMic())
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0x122)
END_HANDLERS

BEGIN_PROPSYNCS(FxSend)
    SYNC_PROP_SET(next_send, mNextSend, SetNextSend(_val.Obj<FxSend>(0)))
    SYNC_PROP_SET(stage, mStage, SetStage(_val.Int(0)))
    SYNC_PROP_MODIFY(dry_gain, mDryGain, UpdateMix())
    SYNC_PROP_MODIFY(wet_gain, mWetGain, UpdateMix())
    SYNC_PROP_MODIFY(input_gain, mInputGain, UpdateMix())
    SYNC_PROP_MODIFY(reverb_mix_db, mReverbMixDb, UpdateMix())
    SYNC_PROP_MODIFY(reverb_enable, mReverbEnable, RebuildChain())
    SYNC_PROP_MODIFY(channels, (int&)mChannels, RebuildChain())
    SYNC_PROP_MODIFY(bypass, mBypass, UpdateMix())
END_PROPSYNCS