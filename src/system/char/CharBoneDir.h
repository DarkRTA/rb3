#ifndef CHAR_CHARBONEDIR_H
#define CHAR_CHARBONEDIR_H
#include "obj/Dir.h"
#include "obj/ObjPtr_p.h"
#include "char/CharBone.h"
#include "char/CharBones.h"
#include <list>

class CharBoneDir : public ObjectDir {
public:

    class Recenter {
    public:
        Recenter(Hmx::Object* o) : mTargets(o, kObjListNoNull), mAverage(o, kObjListNoNull), mSlide(0) {}
        ObjPtrList<CharBone, ObjectDir> mTargets;
        ObjPtrList<CharBone, ObjectDir> mAverage;
        bool mSlide;
    };

    CharBoneDir();
    OBJ_CLASSNAME(CharBoneDir);
    OBJ_SET_TYPE(CharBoneDir);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~CharBoneDir();
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);

    DataNode GetContextFlags();

    static CharBoneDir* FindResource(const char*);
    static void StuffBones(CharBones&, Symbol);
    
    Recenter mRecenter;
    int mMoveContext;
    bool mBakeOutFacing;
    DataNode mContextFlags;
    int mFilterContext;
    ObjPtrList<CharBone, ObjectDir> mFilterBones;
    std::list<String> mFilterNames;
};

#endif
