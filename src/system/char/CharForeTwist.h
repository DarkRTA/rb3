#ifndef CHAR_CHARFORETWIST_H
#define CHAR_CHARFORETWIST_H
#include "char/CharPollable.h"
#include "rndobj/Highlightable.h"
#include "obj/ObjPtr_p.h"
#include "rndobj/Trans.h"

class CharForeTwist : public CharPollable, public RndHighlightable {
public:
    CharForeTwist();
    OBJ_CLASSNAME(CharForeTwist);
    OBJ_SET_TYPE(CharForeTwist);
    virtual DataNode Handle(DataArray*, bool);
    virtual void Poll();
    virtual ~CharForeTwist(){}
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void Highlight(){}

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;
    
    ObjPtr<RndTransformable, ObjectDir> mHand; // 0x10
    ObjPtr<RndTransformable, ObjectDir> mTwist2; // 0x1c
    float mOffset; // 0x28
    float mBias; // 0x2c
};

#endif
