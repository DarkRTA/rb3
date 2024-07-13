#ifndef CHAR_CHARWEIGHTSETTER_H
#define CHAR_CHARWEIGHTSETTER_H
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "char/CharDriver.h"

class CharWeightSetter : public CharWeightable, public CharPollable {
public:
    CharWeightSetter();
    OBJ_CLASSNAME(CharWeightSetter);
    OBJ_SET_TYPE(CharWeightSetter);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual void SetWeight(float);
    virtual ~CharWeightSetter(){}
    virtual void Poll();
    virtual void PollDeps(std::list<Hmx::Object*>&, std::list<Hmx::Object*>&);

    DECLARE_REVS;
    NEW_OVERLOAD;
    DELETE_OVERLOAD;

    ObjPtr<CharWeightable, ObjectDir> mBase; // 0x20
    ObjPtr<CharDriver, ObjectDir> mDriver; // 0x2c
    ObjPtrList<CharWeightSetter, ObjectDir> mMinWeights; // 0x38
    ObjPtrList<CharWeightSetter, ObjectDir> mMaxWeights; // 0x48
    int mFlags; // 0x58
    float mOffset; // 0x5c
    float mScale; // 0x60
    float mBaseWeight; // 0x64
    float mBeatsPerWeight; // 0x68
};

#endif