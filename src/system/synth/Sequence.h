#pragma once
#include "obj/Object.h"
#include "synth/Pollable.h"
#include "utl/FilePath.h"
#include "obj/ObjPtr_p.h"
#include "synth/Faders.h"
#include <list>

class SeqInst;

/** "A set of audio tasks" */
class Sequence : public Hmx::Object, public SynthPollable {
public:
    Sequence();
    virtual ~Sequence();
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    
    virtual const char* GetSoundDisplayName(){ return MakeString("Sequence: %s", Name()); }
    virtual SeqInst* MakeInstImpl() = 0;
    virtual void SynthPoll();

    static void Init();

    SeqInst* MakeInst();
    /** "Play the sequence" */
    SeqInst* Play(float, float, float);
    DataNode OnPlay(DataArray*);
    void OnTriggerSound(int);
    /** "Stop all instances of this sequence" */
    void Stop(bool);
    
    ObjPtrList<SeqInst> mInsts; // 0x28
    /** "Average volume this sequence will be played at, in dB" */
    float mAvgVol; // 0x38
    /** "Amount to vary the volume above and below the average, in dB" */
    float mVolSpread; // 0x3c
    /** "Average transpose this sequence will be played at, in semitones" */
    float mAvgTranspose; // 0x40
    /** "Amount to vary the transpose, in semitones" */
    float mTransposeSpread; // 0x44
    /** "Average pan to apply to this sequence (-1 - 1)" */
    float mAvgPan; // 0x48
    /** "Amount to vary the pan" */
    float mPanSpread; // 0x4c
    FaderGroup mFaders; // 0x50
    /** "If false, this sequence will play to its end and can't be stopped prematurely" */
    bool mCanStop; // 0x64
};

/** "A Sequence type which just waits a specified duration, generating
 *  no sound.  Useful for tweaking the timing of other events." */
class WaitSeq : public Sequence {
public:
    WaitSeq();
    virtual ~WaitSeq(){}
    OBJ_CLASSNAME(WaitSeq);
    OBJ_SET_TYPE(WaitSeq);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();

    float AvgWaitSecs() const { return mAvgWaitSecs; }
    float WaitSpread() const { return mWaitSpread; }

    NEW_OBJ(WaitSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(WaitSeq)
    }

    /** "Average wait time, in seconds" */
    float mAvgWaitSecs; // 0x68
    /** "Amount to vary the wait time, in seconds" */
    float mWaitSpread; // 0x6c
};

/** "A sequence which plays other sequences.  Abstract base class." */
class GroupSeq : public Sequence {
public:
    GroupSeq();
    virtual ~GroupSeq(){}
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    ObjPtrList<Sequence>& Children(){ return mChildren; }

    /** "The children of this sequence" */
    ObjPtrList<Sequence> mChildren; // 0x68
};

/** "Plays one or more of its child sequences, selected at random." */
class RandomGroupSeq : public GroupSeq {
public:
    RandomGroupSeq();
    virtual ~RandomGroupSeq(){}
    OBJ_CLASSNAME(RandomGroupSeq);
    OBJ_SET_TYPE(RandomGroupSeq);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();

    int NextIndex();
    void PickNextIndex();
    void ForceNextIndex(int);
    int GetNumSimul(){ return mNumSimul; }
    void AddToPlayedHistory(int idx){
        if(!mAllowRepeats){
            if(mPlayHistory.size() != 0){
                unsigned int plays = mPlayHistory.size();
                int cap = mChildren.size() - 1;
                if(plays == cap){
                    int numChildren = mChildren.size();
                    for(int i = 0; i < numChildren / 2; i++){
                        mPlayHistory.pop_front();
                    }
                }
            }
            mPlayHistory.push_back(idx);
        }
    }
    bool AllowRepeats() const { return mAllowRepeats; }
    bool InPlayedHistory(int idx) const {
        std::list<int>::const_reverse_iterator it;
        for(it = mPlayHistory.rbegin(); it != mPlayHistory.rend(); it++){
            if(*it == idx) return true;
        }
        return false;
    }

    NEW_OBJ(RandomGroupSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(RandomGroupSeq)
    }

    /** "Number of children to play simultaneously" */
    int mNumSimul; // 0x78
    /** "If false, you will never hear the same sequence again until all have played (only if num_simul is 1)" */
    bool mAllowRepeats; // 0x7c
    int mNextIndex; // 0x80
    int mForceChooseIndex; // 0x84
    std::list<int> mPlayHistory; // 0x88
};

/** "Plays all of its child sequences at random intervals" */
class RandomIntervalGroupSeq : public GroupSeq {
public:
    RandomIntervalGroupSeq();
    virtual ~RandomIntervalGroupSeq(){}
    OBJ_CLASSNAME(RandomIntervalGroupSeq);
    OBJ_SET_TYPE(RandomIntervalGroupSeq);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();

    NEW_OBJ(RandomIntervalGroupSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(RandomIntervalGroupSeq)
    }

    /** "the number of seconds on average we wait to play a child cue again" */
    float mAvgIntervalSecs; // 0x78
    /** "We randomly deviate + or - this many seconds from the average when picking our wait interval" */
    float mIntervalSpread; // 0x7c
    /** "the maximum number of sounds we allow at one time" */
    int mMaxSimultaneous; // 0x80
};

/** "Plays its child sequences in order, waiting for each to stop
 *  before moving on to the next." */
class SerialGroupSeq : public GroupSeq {
public:
    SerialGroupSeq(){}
    virtual ~SerialGroupSeq(){}
    OBJ_CLASSNAME(SerialGroupSeq);
    OBJ_SET_TYPE(SerialGroupSeq);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();

    NEW_OBJ(SerialGroupSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(SerialGroupSeq)
    }
};

/** "Plays all of its child sequences at the same time." */
class ParallelGroupSeq : public GroupSeq {
public:
    ParallelGroupSeq(){}
    virtual ~ParallelGroupSeq(){}
    OBJ_CLASSNAME(ParallelGroupSeq);
    OBJ_SET_TYPE(ParallelGroupSeq);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);
    virtual SeqInst* MakeInstImpl();

    NEW_OBJ(ParallelGroupSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(ParallelGroupSeq)
    }
};

class SfxSeq : public SerialGroupSeq {
public:
    SfxSeq();
    virtual ~SfxSeq(){}
    OBJ_CLASSNAME(SfxSeq);
    OBJ_SET_TYPE(SfxSeq);
    virtual void Save(BinStream&);
    virtual void Load(BinStream&);

    NEW_OBJ(SfxSeq)
    static void Init(){
        REGISTER_OBJ_FACTORY(SfxSeq)
    }
};
