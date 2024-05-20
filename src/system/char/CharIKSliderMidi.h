#ifndef CHAR_CHARIKSLIDERMIDI_H
#define CHAR_CHARIKSLIDERMIDI_H
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "rndobj/Highlightable.h"
#include "char/Character.h"

class CharIKSliderMidi : public RndHighlightable, public CharWeightable, public CharPollable {
public:
    CharIKSliderMidi();
    virtual ~CharIKSliderMidi();
    virtual void Highlight();
    OBJ_CLASSNAME(CharIKSliderMidi);
    OBJ_SET_TYPE(CharIKSliderMidi);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual void Enter();
    virtual void SetName(const char*, class ObjectDir*);

    void SetupTransforms();
    void SetFraction(float, float);

    DECLARE_REVS;
    DELETE_OVERLOAD;

    ObjPtr<RndTransformable, ObjectDir> mTarget;
    ObjPtr<RndTransformable, ObjectDir> mFirstSpot;
    ObjPtr<RndTransformable, ObjectDir> mSecondSpot;
    Vector3 mDestPos;
    Vector3 mOldPos;
    Vector3 mCurPos;
    float mTargetPercentage;
    float mOldPercentage;
    float mFrac;
    float mFracPerBeat;
    bool mPercentageChanged;
    bool mResetAll;
    ObjPtr<Character, ObjectDir> mMe;
    float mTolerance;
};

#endif
