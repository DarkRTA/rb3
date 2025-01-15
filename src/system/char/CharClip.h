#pragma once
#include "char/CharBones.h"
#include "obj/Data.h"
#include "obj/ObjMacros.h"
#include "obj/Object.h"
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"
#include "char/CharBonesSamples.h"
#include "math/Key.h"
#include "utl/BinStream.h"

class CharBoneDir;

struct CharGraphNode {
    /** "where to blend from in my clip" */
    float curBeat;
    /** "where to blend to in clip" */
    float nextBeat;
};

/** "This is the simple form that stores
 *  samples and linearly interpolates between them. 
 *  Data is grouped by keyframe, for better RAM coherency
 *  better storage, interpolation, etc." */
class CharClip : public Hmx::Object {
public:

    class NodeVector {
    public:
        NodeVector* Next() const {
            return (NodeVector*)(this->nodes + size);
        }
        /** "clip it's transitioning to" */
        CharClip* clip; // 0x0
        int size; // 0x4
        CharGraphNode nodes[1]; // 0x8
    };

    class Transitions {
    public:
        Transitions(Hmx::Object*);
        ~Transitions();
        void Clear();
        NodeVector* Resize(int, const CharClip::NodeVector*);
        NodeVector* FindNodes(CharClip*) const;
        void RemoveNodes(CharClip*);
        int Size() const;
        void Replace(Hmx::Object*, Hmx::Object*);
        int BytesInMemory() const {
            return (int)mNodeEnd - (int)mNodeStart;
        }
        NodeVector* GetNodes(int) const;
        void Load(BinStream&);
        void AddNode(CharClip*, const CharGraphNode&);

        NodeVector* mNodeStart; // 0x0
        NodeVector* mNodeEnd; // 0x4
        Hmx::Object* mOwner; // 0x8
    };

    class BeatEvent {
    public:
        BeatEvent();
        BeatEvent(const BeatEvent&);
        BeatEvent& operator=(const BeatEvent&);
        void Load(BinStream&);

        /** "The handler to call on the CharClip" */
        Symbol event;
        /** "Beat the event should trigger" */
        float beat;
    };

    class FacingSet {
    public:
        class FacingBones : public CharBones {
        public:
            FacingBones();
            virtual ~FacingBones(){}
            virtual void ReallocateInternal();

            void Set(bool);

            Vector3 mDeltaPos; // 0x50
            float mDeltaAng; // 0x5c
        };

        FacingSet();
        void ListBones(std::list<CharBones::Bone>&);
        void Set(CharBonesSamples&);
        void ScaleDown(CharBones&, float);
        void ScaleAddSample(CharBonesSamples&, CharBones&, float, int, float, int, float);

        static void Init();
        static FacingBones sFacingPos;
        static FacingBones sFacingRotAndPos;
        
        short mFullRot; // 0x0
        short mFullPos; // 0x2
        FacingBones* mFacingBones; // 0x4
        float mWeight; // 0x8
    };

    /** "Blend mode, if any, to use by default for this clip" */
    enum DefaultBlend {
        kPlayNoDefault = 0,
        kPlayNow = 1,
        kPlayNoBlend = 2,
        kPlayFirst = 3,
        kPlayLast = 4,
        kPlayDirty = 8
    };
    
    /** "Looping mode, if any, to use by default for this clip" */
    enum DefaultLoop {
        kPlayNoLoop = 0x10,
        kPlayLoop = 0x20,
        kPlayGraphLoop = 0x30,
        kPlayNodeLoop = 0x40
    };

    /** "Time units/alignment, if any, for this clip" */
    enum BeatAlignMode {
        kPlayBeatTime = 0,
        kPlayRealTime = 0x200,
        kPlayUserTime = 0x400,
        kPlayBeatAlign1 = 0x1000,
        kPlayBeatAlign2 = 0x2000,
        kPlayBeatAlign4 = 0x4000,
        kPlayBeatAlign8 = 0x8000
    };

    CharClip();
    virtual ~CharClip();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(CharClip);
    OBJ_SET_TYPE(CharClip);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void PreSave(BinStream&);
    virtual void PostSave(BinStream&);
    virtual void Print();
    virtual void Export(DataArray*, bool);
    virtual void SetTypeDef(DataArray*);

    CharBoneDir* GetResource() const;
    int GetContext() const;
    void ListBones(std::list<CharBones::Bone>&);
    void StuffBones(CharBones&);
    void PoseMeshes(ObjectDir*, float);
    void SetPlayFlags(int);
    bool SharesGroups(CharClip*);
    /** "average beats per second" */
    float AverageBeatsPerSecond() const;
    void ScaleDown(CharBones&, float);
    void RotateBy(CharBones&, float);
    void ScaleAdd(CharBones&, float, float, float);
    /** "Length in seconds" */
    float LengthSeconds() const;
    void SetFlags(int);
    void SetDefaultBlend(int);
    void SetDefaultLoop(int);
    void SetBeatAlignMode(int);
    void SetRelative(CharClip*);
    int AllocSize();
    void MakeMRU();
    bool InGroup(Hmx::Object*);
    int InGroups();
    void EvaluateChannel(void*, const void*, float);
    void SortEvents();
    CharGraphNode* FindFirstNode(CharClip*, float) const;
    CharGraphNode* FindLastNode(CharClip*, float) const;
    CharGraphNode* FindNode(CharClip*, float, int, float) const;
    float FrameToBeat(float) const;
    float BeatToFrame(float) const;
    float DeltaSecondsToDeltaBeat(float, float);
    int BeatToSample(float, float*) const;
    float SampleToBeat(int) const;
    void RotateTo(CharBones&, float, float);
    void Relativize();

    CharClip* Relative() const { return mRelative; }
    float Range() const { return mRange; }
    int Flags() const { return mFlags; }
    int PlayFlags() const { return mPlayFlags; }
    RndAnimatable* SyncAnim() const { return mSyncAnim; }
    /** "Start beat, beat this clip starts at" */
    float StartBeat() const { return mBeatTrack.front().value; }
    /** "End beat, beat this clip ends at" */
    float EndBeat() const { return mBeatTrack.back().value; }
    /** "Length in beats" */
    float LengthBeats() const { return EndBeat() - StartBeat(); }
    /** "Number of original samples taken, pre-keyframe compression" */
    int NumFrames() const {
        return Max<int>(Max<int>(1, mFull.mNumSamples), mFull.mFrames.size());
    }
    void* GetChannel(Symbol);
    int TransitionVersion();
    void EvaluateChannel(void*, const void*, int, float);
    void ScaleAddSample(CharBones&, float, int, float, int, float);
    void SetFacingFull(){
        mFacing.Set(mFull);
    }

    DataNode OnGroups(DataArray*);
    DataNode OnHasGroup(DataArray*);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharClip)
    static void Init();
    static const char* BeatAlignString(int);
    static void LockAndDelete(CharClip**, int, int);
    static void Register(){
        REGISTER_OBJ_FACTORY(CharClip);
    }
    static void SetDefaultBlendFlag(int& mask, int blendFlag){
        mask = mask & 0xfffffff0 | blendFlag;
    }
    static void SetDefaultLoopFlag(int& mask, int loopFlag){
        mask = mask & 0xffffff0f | loopFlag;
    }
    static void SetDefaultBeatAlignModeFlag(int& mask, int alignFlag){
        mask = mask & 0xffff09ff | alignFlag;
    }
    
    Transitions mTransitions; // 0x1c
    /** "Frames per second" */
    float mFramesPerSec; // 0x28
    Keys<float, float> mBeatTrack; // 0x2c
    /** "Search flags, app specific" */
    int mFlags; // 0x34
    int mPlayFlags; // 0x38
    /** "Range in frames to randomly offset by when playing" */
    float mRange; // 0x3c
    /** "Indicates transition graph needs updating" */
    bool mDirty; // 0x40
    bool mDoNotCompress; // 0x41
    short mOldVer; // 0x42
    /** "Make the clip all relative to this other clip's first frame" */
    ObjPtr<CharClip> mRelative; // 0x44
    /** "Events that get triggered during play" */
    std::vector<BeatEvent> mBeatEvents; // 0x50
    /** "An animatable, like a PropAnim, you'd like play in sync with this clip" */
    ObjPtr<RndAnimatable> mSyncAnim; // 0x58
    CharBonesSamples mFull; // 0x64
    CharBonesSamples mOne; // 0xc4
    FacingSet mFacing; // 0x124
    std::vector<CharBones::Bone> mZeros; // 0x130 - change vector type
};
