#ifndef CHAR_CHARCLIP_H
#define CHAR_CHARCLIP_H
#include "obj/Object.h"
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"
#include "char/CharBonesSamples.h"
#include "utl/Key.h"

struct CharGraphNode {
    float curBeat;
    float nextBeat;
};

class CharClip : public Hmx::Object {
public:

    class NodeVector {
    public:
        CharClip* clip;
        int size;
        CharGraphNode nodes[1];
    };

    class Transitions {
    public:
        Transitions(Hmx::Object*);
        
        NodeVector* mNodeStart;
        NodeVector* mNodeEnd;
        Hmx::Object* mOwner;
    };

    class BeatEvent {
    public:
        Symbol event;
        float beat;
    };

    struct FacingBones : public CharBones {
        Vector3 mDeltaPos;
        float mDeltaAng;
    };

    struct FacingSet {
        FacingSet();
        
        short mFullRot;
        short mFullPos;
        FacingBones* mFacingBones;
        float mWeight;
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
    
    Transitions mTransitions;
    float mFramesPerSec;
    Keys<float, float> mBeatTrack;
    int mFlags;
    int mPlayFlags;
    float mRange;
    bool mDirty;
    bool mDoNotCompress;
    short unk42;
    ObjPtr<CharClip, ObjectDir> mRelative;
    std::vector<BeatEvent> mBeatEvents;
    ObjPtr<RndAnimatable, ObjectDir> mSyncAnim;
    CharBonesSamples mFull;
    CharBonesSamples mOne;
    FacingSet mFacing;
    std::vector<int> mZeros; // change vector type
};

#endif