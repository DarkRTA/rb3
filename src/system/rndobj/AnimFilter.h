#ifndef RNDOBJ_ANIMFILTER_H
#define RNDOBJ_ANIMFILTER_H
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"



class RndAnimFilter : public RndAnimatable {
public:
    enum Type {
        kRange = 0,
        kLoop = 1,
        kShuttle = 2,
    };
    RndAnimFilter();
    OBJ_CLASSNAME(AnimFilter);
    OBJ_SET_TYPE(AnimFilter);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndAnimFilter(){}
    virtual bool Loop(){ return mType >= kLoop; }
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual RndAnimatable* AnimTarget(){
        return mAnim.Ptr() ? mAnim.Ptr() : 0;
    }
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;

    float Scale();
    void SetAnim(RndAnimatable*);
    DataNode OnSafeAnims(DataArray*);

    DECLARE_REVS;

    ObjPtr<RndAnimatable, class ObjectDir> mAnim; // offset 0x10, size 0xC
    float mPeriod; // offset 0x1C, size 0x4
    float mStart; // offset 0x20, size 0x4
    float mEnd; // offset 0x24, size 0x4
    float mScale; // offset 0x28, size 0x4
    float mOffset; // offset 0x2C, size 0x4
    float mSnap; // offset 0x30, size 0x4
    float mJitter; // offset 0x34, size 0x4
    float mJitterFrame; // offset 0x38, size 0x4
    enum Type mType; // offset 0x3C, size 0x4
};

#endif
