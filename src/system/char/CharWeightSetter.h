#pragma once
#include "char/CharWeightable.h"
#include "char/CharPollable.h"
#include "obj/ObjPtr_p.h"
#include "char/CharDriver.h"

/** "Sets its own weight by pushing flags through a driver to
 *  see what fraction of them it has." */
class CharWeightSetter : public CharWeightable, public CharPollable {
public:
    CharWeightSetter();
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
    NEW_OBJ(CharWeightSetter)
    static void Init(){
        REGISTER_OBJ_FACTORY(CharWeightSetter)
    }

    ObjPtr<CharWeightable> mBase; // 0x20
    ObjPtr<CharDriver> mDriver; // 0x2c
    ObjPtrList<CharWeightSetter> mMinWeights; // 0x38
    ObjPtrList<CharWeightSetter> mMaxWeights; // 0x48
    int mFlags; // 0x58
    float mOffset; // 0x5c
    float mScale; // 0x60
    float mBaseWeight; // 0x64
    float mBeatsPerWeight; // 0x68

    // moved down here so this TU will link
    OBJ_CLASSNAME(CharWeightSetter);
    OBJ_SET_TYPE(CharWeightSetter);
};
