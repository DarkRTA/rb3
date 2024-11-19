#ifndef RNDOBJ_ANIMFILTER_H
#define RNDOBJ_ANIMFILTER_H
#include "rndobj/Anim.h"
#include "obj/ObjPtr_p.h"

/**
* @brief: A filter for an animatable object.
* Original _objects description:
* "An AnimFilter object modifies the playing of another animatable object"
*/
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
    virtual Hmx::Object* AnimTarget(){ return mAnim; }
    virtual void ListAnimChildren(std::list<RndAnimatable*>&) const;

    float Scale();
    void SetAnim(RndAnimatable*);
    DataNode OnSafeAnims(DataArray*);
    
    Type GetType(){ return mType; }
    RndAnimatable* Anim(){ return mAnim; }
    float Start(){ return mStart; }
    float End(){ return mEnd; }
    float Period(){ return mPeriod; }
    float FrameOffset(){
        float ret = mStart;
        if(mEnd >= mStart) ret = 0.0f;
        else ret -= mEnd;
        return mOffset + ret;
    }

    NEW_OVERLOAD;
    DECLARE_REVS;
    NEW_OBJ(RndAnimFilter);
    static void Init(){
        REGISTER_OBJ_FACTORY(RndAnimFilter)
    }

    /** "Animatable object that receives filtered frame" */
    ObjPtr<RndAnimatable> mAnim; // 0x10
    /** "Alternative to scale, overriden period of animation" */
    float mPeriod; // 0x1C
    /** "Overriden start frame of animation" */
    float mStart; // 0x20
    /** "Overriden end frame of animation" */
    float mEnd; // 0x24
    /** "Multiplier to speed of animation" */
    float mScale; // 0x28
    /** "Amount to offset frame for animation" */
    float mOffset; // 0x2C
    /** "Snap frame to nearest multiple" */
    float mSnap; // 0x30
    /** "Jitter frame randomly up to this amount" */
    float mJitter; // 0x34
    float mJitterFrame; // 0x38
    /** "How to treat the frame outside of start and end" */
    Type mType; // 0x3C
};

#endif
