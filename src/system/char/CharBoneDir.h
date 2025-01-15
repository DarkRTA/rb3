#pragma once
#include "obj/Dir.h"
#include "obj/ObjMacros.h"
#include "obj/ObjPtr_p.h"
#include "char/CharBone.h"
#include "char/CharBones.h"
#include <list>

/** "A CharBone container, acts as a resource file, storing skeleton and DOF for particular contexts" */
class CharBoneDir : public ObjectDir {
public:

    class Recenter {
    public:
        Recenter(Hmx::Object* o) : mTargets(o), mAverage(o), mSlide(0) {}

        /** "bones to recenter, ie, bone_pelvis" */
        ObjPtrList<CharBone> mTargets; // 0x0
        /** "bones to average to find the new center" */
        ObjPtrList<CharBone> mAverage; // 0x10
        /** "Slide the character over the course of the clip.  If false, just uses the start of the clip" */
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
    NEW_OBJ(CharBoneDir)
    static void Register(){
        REGISTER_OBJ_FACTORY(CharBoneDir)
    }
    
    /** "Used to limit travel.  Moves [targets] bones so that the average of the [average] bones will be at (0,0,0) at the start of the clip.  
     *  If slide is true evaluates the [average] bones and the start of the clip and end of the clip, and recenters [targets] smoothly between those." */
    Recenter mRecenter; // 0x80
    /** "context in which character should move itself around via bone_facing.pos and bone_facing.rotz bones" */
    int mMoveContext; // 0xa4
    /** "if false, won't bake out facing, will just bake out position" */
    bool mBakeOutFacing; // 0xa8
    DataNode mContextFlags; // 0xac
    /** "Context to use for listing filter_bones" */
    int mFilterContext; // 0xb4
    /** "bones with context specified in filter_context" */
    ObjPtrList<CharBone> mFilterBones; // 0xb8
    /** "name of bone with context specified in filter_context" */
    std::list<String> mFilterNames; // 0xc8
};
