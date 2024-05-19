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

    DECLARE_REVS;
    DELETE_OVERLOAD;
    
    ObjPtr<RndTransformable, ObjectDir> mBone;
    ObjPtr<RndTransformable, ObjectDir> mCurSpot;
    ObjPtr<RndTransformable, ObjectDir> mNewSpot;
    Transform mLocalXfm;
    Transform mOldLocalXfm;
    float mFrac;
    float mFracPerBeat;
    bool mSpotChanged;
    ObjPtr<CharWeightable, ObjectDir> mAnimBlender;
    float mMaxAnimBlend;
    float mAnimFracPerBeat;
    float mAnimFrac;
};

#endif
