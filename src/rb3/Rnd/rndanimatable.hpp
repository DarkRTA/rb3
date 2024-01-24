#ifndef RND_RNDANIMATABLE_HPP
#define RND_RNDANIMATABLE_HPP
#include "hmx/object.hpp"

class RndAnimatable : public virtual Hmx::Object {
public:
    RndAnimatable();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndAnimatable();
    virtual void Loop(); // StubZero
    virtual void StartAnim(); // StubVoid
    virtual void EndAnim(); // StubVoid
    virtual void SetFrame(float, float);
    virtual float StartFrame(); // StubZerof
    virtual float EndFrame(); // StubZerof
    virtual RndAnimatable* AnimTarget();
    virtual void SetKey(float); // StubVoid

    // symbol from GDRB: ListAnimChildren__13RndAnimatableCFRQ211stlpmtx_std70list<P13RndAnimatable,Q211stlpmtx_std30StlNodeAlloc<P13RndAnimatable>>
    virtual void ListAnimChildren(); // StubVoid

    static Symbol StaticClassName();

    DataNode OnAnimate(DataArray*);
    void StopAnimation();
    bool IsAnimating();
    DataNode OnConvertFrames(DataArray*);

    float frame;
    int rate;
};

#endif
