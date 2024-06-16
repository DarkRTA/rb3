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

typedef void(FaderGroup::*FaderGroupFunc)(void);

void Fader::UpdateValue(float val){
    mVal = val;

    FaderGroupFunc funcs[2];
    funcs[0] = funcs[1] = FaderGroup::ClearDirty;
    std::set<FaderGroup*>::iterator it = mClients.begin();

    for (;it != mClients.end(); it++) {
        ((*it)->*funcs[1])();
    }
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

FaderGroup::FaderGroup(Hmx::Object* o) : mFaders(o, kObjListNoNull), mDirty(true) {

}

FaderGroup::~FaderGroup(){
    while(mFaders.size() != 0){
        Fader* frontObj = mFaders.front();
        mFaders.pop_front();
        frontObj->RemoveClient(this);
        if(!frontObj->mLocalName.Null()){
            delete frontObj;
        }
    }
}

Fader* FaderGroup::AddLocal(Symbol name){
    MILO_ASSERT(!name.Null(), 0xEA);
    ObjPtrList<Fader, ObjectDir>::iterator it = mFaders.begin();
    for(; it != mFaders.end(); ++it){
        if((*it)->mLocalName == name) return *it;
    }
    Fader* f = Hmx::Object::New<Fader>();
    f->mLocalName = name;
    f->AddClient(this);
    mFaders.push_back(f);
    mDirty = true;
    return f;
}

void FaderGroup::Add(Fader* f){
    ObjPtrList<Fader, ObjectDir>::iterator it = mFaders.begin();
    for(; it != mFaders.end(); ++it){
        if(*it == f) return;
    }
    f->AddClient(this);
    mFaders.push_back(f);
    mDirty = true;
}

void FaderGroup::Remove(Fader* f){
    for(ObjPtrList<Fader, ObjectDir>::iterator it = mFaders.begin(); it != mFaders.end(); ++it){
        if(*it == f){
            f->RemoveClient(this);
            mFaders.erase(it);
            mDirty = true;
            return;
        }
    }
}

float FaderGroup::GetVal(){
    float sum = 0.0f;
    for(ObjPtrList<Fader, ObjectDir>::iterator it = mFaders.begin(); it != mFaders.end(); ++it){
        sum += (*it)->mVal;
    }
    return sum;
}

bool FaderGroup::Dirty(){ return mDirty; }
void FaderGroup::SetDirty(){ mDirty = true; }
void FaderGroup::ClearDirty(){ mDirty = false; }

Fader* FaderGroup::FindLocal(Symbol sym, bool fail){
    if(!sym.Null()){
        for(ObjPtrList<Fader, ObjectDir>::iterator it = mFaders.begin(); it != mFaders.end(); ++it){
            if((*it)->mLocalName == sym) return *it;
        }
    }
    if(fail) MILO_FAIL("bad local fader: %s", sym);
    return 0;
}

void FaderGroup::Print(TextStream& ts){
    ts << "FaderGroup (size " << mFaders.size() << ")\n";
    for(ObjPtrList<Fader, ObjectDir>::iterator it = mFaders.begin(); it != mFaders.end(); ++it){
        String str((*it)->mLocalName.Str());
        if(str.empty()) str = (*it)->Name();
        else str += "(local)";
        if(str.empty()) str = "(anon)";
        float val = (*it)->mVal;
        ts << "  " << str << ": " << val << "\n";
    }
}

DECOMP_FORCEACTIVE(Faders, "ObjPtr_p.h", "c.Owner()", "")

#define kGroupRev 0

// fn_80670CA8
void FaderGroup::Load(BinStream& bs){
    int rev;
    bs >> rev;
    MILO_ASSERT(rev <= kGroupRev, 0x187);
    ObjPtrList<Fader, ObjectDir> pList(mFaders.mOwner, kObjListNoNull);
    bs >> pList;
    for(ObjPtrList<Fader, ObjectDir>::iterator it = mFaders.begin(); it != mFaders.end(); it){
        Fader* f = *it++;
        bool b = false;
        if(f->Dir() && f->mLocalName.Null()){
            b = true;
        }
        if(b) Remove(f);
    }
    for(ObjPtrList<Fader, ObjectDir>::iterator it = pList.begin(); it != pList.end(); ++it){
        Add(*it);
    }
}

// fn_80670F64
bool PropSync(FaderGroup& grp, DataNode& node, DataArray* prop, int i, PropOp op){
    ObjPtrList<Fader, ObjectDir> pList(grp.mFaders);
    for(ObjPtrList<Fader, ObjectDir>::iterator it = pList.begin(); it != pList.end(); it){
        Fader* f = *it;
        bool b = false;
        if(f->Dir() && f->mLocalName.Null()){
            b = true;
        }
        if(b) it++;
        else it = pList.erase(it);
        // else it++;
        // pList.erase(it++);
    }
    bool sync = PropSync(pList, node, prop, i, op);
    for(ObjPtrList<Fader, ObjectDir>::iterator it = grp.mFaders.begin(); it != grp.mFaders.end(); it){
        Fader* f = *it++;
        bool b = false;
        if(f->Dir() && f->mLocalName.Null()){
            b = true;
        }
        if(b) grp.Remove(f);
    }
    for(ObjPtrList<Fader, ObjectDir>::iterator it = pList.begin(); it != pList.end(); ++it){
        grp.Add(*it);
    }
    return sync;
}

FaderTask::FaderTask() : mTimer(), mInterp(0), mFader(0), mDone(0) {

}

FaderTask::~FaderTask(){
    delete mInterp;
    mInterp = 0;
}

void FaderTask::PollAll(){
    for(std::list<FaderTask*>::iterator it = sTasks.begin(); it != sTasks.end(); it){
        if((*it)->mDone){
            delete *it;
            it = sTasks.erase(it);
        }
        else {
            (*it)->Poll();
            it++;
        }
    }
}

void FaderTask::Poll(){
    MILO_ASSERT(!mDone, 0x1DE);
    MILO_ASSERT(mInterp != NULL, 0x1DF);
    float f = mTimer.SplitMs();
    if (f > mInterp->mX1) {
        mFader->UpdateValue(mInterp->mY1);
        mFader->CancelFade();
    } else {
        mFader->UpdateValue(mInterp->Eval(f));
    }
}

void Fader::Check(){
    MILO_ASSERT(mFaderTask != (FaderTask*)0x01000000, 0x20C);
    MILO_ASSERT(mFaderTask != NULL, 0x20D);
}

DECOMP_FORCEFUNC(Faders, Fader, SetType)
DECOMP_FORCEFUNC_TEMPL(Faders, ObjPtrList, Replace(0, 0), Fader, ObjectDir)
DECOMP_FORCEFUNC_TEMPL(Faders, ObjPtrList, RefOwner(), Fader, ObjectDir)
