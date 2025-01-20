#pragma once
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"
#include "rndobj/Highlightable.h"
#include "char/Character.h"

/** "Moves an RndTransformable (bone) to a percentage of the way between two spots." */
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
    NEW_OBJ(CharIKSliderMidi)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharIKSliderMidi)
    }

    /** "The bone to move" */
    ObjPtr<RndTransformable> mTarget; // 0x28
    /** "Spot at 0%" */
    ObjPtr<RndTransformable> mFirstSpot; // 0x34
    /** "Spot at 100%" */
    ObjPtr<RndTransformable> mSecondSpot; // 0x40
    Vector3 mDestPos; // 0x4c
    Vector3 mOldPos; // 0x58
    Vector3 mCurPos; // 0x64
    float mTargetPercentage; // 0x70
    float mOldPercentage; // 0x74
    float mFrac; // 0x78
    float mFracPerBeat; // 0x7c
    bool mPercentageChanged; // 0x80
    bool mResetAll; // 0x81
    ObjPtr<Character> mMe; // 0x84
    /** "Only move if percentage changes more than this (0.0 - 1.0)" */
    float mTolerance; // 0x90
};
