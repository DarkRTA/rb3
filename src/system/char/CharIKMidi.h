#ifndef CHAR_CHARIKMIDI_H
#define CHAR_CHARIKMIDI_H
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "rndobj/Highlightable.h"
#include "char/Character.h"

class CharIKMidi : public RndHighlightable, public CharPollable {
public:
    CharIKMidi();
    virtual ~CharIKMidi();
    virtual void Highlight();
    OBJ_CLASSNAME(CharIKMidi);
    OBJ_SET_TYPE(CharIKMidi);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual void Enter();

    void NewSpot(RndTransformable*, float);

    DECLARE_REVS;
    DELETE_OVERLOAD;
    
    ObjPtr<RndTransformable, ObjectDir> mBone; // 0x10
    ObjPtr<RndTransformable, ObjectDir> mCurSpot; // 0x1c
    ObjPtr<RndTransformable, ObjectDir> mNewSpot; // 0x28
    Transform mLocalXfm; // 0x34
    Transform mOldLocalXfm; // 0x64
    float mFrac; // 0x94
    float mFracPerBeat; // 0x98
    bool mSpotChanged; // 0x9c
    ObjPtr<CharWeightable, ObjectDir> mAnimBlender; // 0xa0
    float mMaxAnimBlend; // 0xac
    float mAnimFracPerBeat; // 0xb0
    float mAnimFrac; // 0xb4
};

#endif
