#include "synth/Faders.h"
#include "utl/Symbols.h"

static std::vector<Fader*> sFaderList;
std::list<FaderTask*> FaderTask::sTasks;

Fader::Fader() : mVal(0.0f), mFaderTask(0), mLocalName(), mMode(kLinear) {

}

Fader::~Fader(){
    CancelFade();
}

void Fader::SetVal(float f){
    CancelFade();
    UpdateValue(f);
}

void Fader::SetMode(Fader::Mode mode){
    MILO_ASSERT(mFaderTask == NULL, 0x2C);
    mMode = mode;
}

void Fader::DoFade(float targetDb, float duration){
    CancelFade();
    MILO_ASSERT(duration >= 0.0f, 0x35);
    mFaderTask = new FaderTask();
    MILO_ASSERT(mFaderTask != NULL, 0x3B);
    MILO_ASSERT(mFaderTask != (FaderTask*)0x01000000, 0x3C);
    switch(mMode){
        case kLinear:
            mFaderTask->mInterp = new LinearInterpolator(mVal, targetDb, 0.0f, duration);
            break;
        case kExp:
            mFaderTask->mInterp = new ExpInterpolator(mVal, targetDb, 0.0f, duration, 2.0f);
            break;
        case kInvExp:
            mFaderTask->mInterp = new InvExpInterpolator(mVal, targetDb, 0.0f, duration, 2.0f);
            break;
        default:
            MILO_ASSERT(false, 0x54);
            break;
    }
    mFaderTask->mTimer.Start();
    mFaderTask->mFader = this;
    mFaderTask->mDone = false;
    FaderTask* thetask = mFaderTask;
    FaderTask::sTasks.push_back(thetask);
}

bool Fader::IsFading() const { return mFaderTask; }

float Fader::GetTargetDb() const {
    if(mFaderTask) return mFaderTask->mInterp->mY1;
    else return mVal;
}

void Fader::AddClient(FaderGroup* group){
    mClients.insert(group);
}

void Fader::RemoveClient(FaderGroup* group){
    mClients.erase(group);
}

void Fader::CancelFade(){
    if(mFaderTask){
        Check();
        mFaderTask->mDone = true;
        mFaderTask = 0;
    }
}

void Fader::UpdateValue(float val){
    mVal = val;
    
}

SAVE_OBJ(Fader, 0x9B)

BEGIN_LOADS(Fader)
    int rev;
    bs >> rev;
    ASSERT_GLOBAL_REV(rev, 0)
    LOAD_SUPERCLASS(Hmx::Object)
    float f;
    bs >> f;
    SetVal(f);
END_LOADS

BEGIN_COPYS(Fader)
    COPY_SUPERCLASS(Hmx::Object)
    CREATE_COPY(Fader)
    if(c){
        SetVal(c->mVal);
    }
END_COPYS

BEGIN_PROPSYNCS(Fader)
    SYNC_PROP_MODIFY(level, mVal, SetVal(mVal))
END_PROPSYNCS

BEGIN_HANDLERS(Fader)
    HANDLE_ACTION(set_val, SetVal(_msg->Float(2)))
    HANDLE_ACTION(fade, DoFade(_msg->Float(2), _msg->Float(3)))
    HANDLE_SUPERCLASS(Hmx::Object)
    HANDLE_CHECK(0xCE)
END_HANDLERS