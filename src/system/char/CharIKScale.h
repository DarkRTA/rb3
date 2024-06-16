#ifndef CHAR_CHARIKSCALE_H
#define CHAR_CHARIKSCALE_H
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

class CharIKScale : public CharWeightable, public CharPollable {
public:
    CharIKScale();
    OBJ_CLASSNAME(CharIKScale);
    OBJ_SET_TYPE(CharIKScale);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~CharIKScale();
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);

    void CaptureBefore();
    void CaptureAfter();

    DECLARE_REVS;
    DELETE_OVERLOAD;
    
    ObjPtr<RndTransformable, ObjectDir> mDest; // 0x20
    float mScale; // 0x2c
    ObjPtrList<RndTransformable, ObjectDir> mSecondaryTargets; // 0x30
    float mBottomHeight; // 0x40
    float mTopHeight; // 0x44
    bool mAutoWeight; // 0x48
};

#endif
