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

    ObjPtr<CharWeightable, ObjectDir> mBase;
    ObjPtr<CharDriver, ObjectDir> mDriver;
    ObjPtrList<CharWeightSetter, ObjectDir> mMinWeights;
    ObjPtrList<CharWeightSetter, ObjectDir> mMaxWeights;
    int mFlags;
    float mOffset;
    float mScale;
    float mBaseWeight;
    float mBeatsPerWeight;
};

#endif