#ifndef CHAR_CHARCLIP_H
#define CHAR_CHARCLIP_H
#include "obj/Object.h"
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"
#include "char/CharBonesSamples.h"
#include "math/Key.h"

class CharBoneDir;

struct CharGraphNode {
    float curBeat;
    float nextBeat;
};

class CharClip : public Hmx::Object {
public:

    class NodeVector {
    public:
        CharClip* clip; // 0x0
        int size; // 0x4
        CharGraphNode nodes[1]; // 0x8
    };

    class Transitions {
    public:
        Transitions(Hmx::Object*);
        ~Transitions();
        void Clear();
        void Resize(int, const CharClip::NodeVector*);
        void RemoveNodes(CharClip*);
        int Size() const;

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

        Symbol event;
        float beat;
    };

    struct FacingBones : public CharBones {
        Vector3 mDeltaPos;
        float mDeltaAng;
    };

    struct FacingSet {
        FacingSet();

        static void Init();
        
        short mFullRot; // 0x0
        short mFullPos; // 0x2
        FacingBones* mFacingBones; // 0x4
        float mWeight; // 0x8
    };

    CharClip();
    virtual ~CharClip();
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
    float AverageBeatsPerSecond() const;
    void ScaleDown(CharBones&, float);
    void RotateBy(CharBones&, float);
    void ScaleAdd(CharBones&, float, float, float);
    float LengthSeconds() const;
    void SetFlags(int);
    void SetDefaultBlend(int);
    void SetDefaultLoop(int);
    void SetBeatAlignMode(int);
    void SetRelative(CharClip*);
    int AllocSize();
    void EvaluateChannel(void*, const void*, float);
    void LockAndDelete(CharClip**, int, int);
    float StartBeat() const { return mBeatTrack.front().value; }
    float EndBeat() const { return mBeatTrack.back().value; }
    float LengthBeats() const { return EndBeat() - StartBeat(); }
    int NumFrames() const {
        return Max<int>(Max<int>(1, mFull.mNumSamples), mFull.mFrames.size());
    }
    char* GetChannel(Symbol);
    int PlayFlags() const { return mPlayFlags; }

    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    NEW_OBJ(CharClip)
    static void Init();
    static const char* BeatAlignString(int);
    
    Transitions mTransitions; // 0x1c
    float mFramesPerSec; // 0x28
    Keys<float, float> mBeatTrack; // 0x2c
    int mFlags; // 0x34
    int mPlayFlags; // 0x38
    float mRange; // 0x3c
    bool mDirty; // 0x40
    bool mDoNotCompress; // 0x41
    short unk42; // 0x42
    ObjPtr<CharClip, ObjectDir> mRelative; // 0x44
    std::vector<BeatEvent> mBeatEvents; // 0x50
    ObjPtr<RndAnimatable, ObjectDir> mSyncAnim; // 0x58
    CharBonesSamples mFull; // 0x64
    CharBonesSamples mOne; // 0xc4
    FacingSet mFacing; // 0x124
    std::vector<int> mZeros; // 0x130 - change vector type
};

#endif