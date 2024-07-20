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
        ObjPtrList<CharBone, ObjectDir> mTargets; // 0x0
        ObjPtrList<CharBone, ObjectDir> mAverage; // 0x10
        bool mSlide; // 0x20
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

    void StuffBones(CharBones&, int);
    void ListBones(std::list<CharBones::Bone>&, int, bool);
    void MergeCharacter(const FilePath&);
    void SyncFilter();
    DataNode GetContextFlags();

    DECLARE_REVS;

    static void Init();
    static void Terminate();
    static CharBoneDir* FindResource(const char*);
    static CharBoneDir* FindResourceFromClipType(Symbol);
    static void StuffBones(CharBones&, Symbol);
    static DataNode GetClipTypes();
    static DataArray* sCharClipTypes;
    
    Recenter mRecenter; // 0x80
    int mMoveContext; // 0xa4
    bool mBakeOutFacing; // 0xa8
    DataNode mContextFlags; // 0xac
    int mFilterContext; // 0xb4
    ObjPtrList<CharBone, ObjectDir> mFilterBones; // 0xb8
    std::list<String> mFilterNames; // 0xc8
};

#endif
