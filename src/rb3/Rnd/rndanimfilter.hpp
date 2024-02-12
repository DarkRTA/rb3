#ifndef RND_RNDANIMFILTER_HPP
#define RND_RNDANIMFILTER_HPP
#include "obj/Object.h"
#include "obj/ObjPtr_p.h"
#include "Rnd/rndanimatable.hpp"

class RndAnimFilter : public RndAnimatable {
public:
    RndAnimFilter();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndAnimFilter();
    virtual void Loop();
    virtual void StartAnim(); // StubVoid
    virtual void EndAnim(); // StubVoid
    virtual void SetFrame(float, float);
    virtual float StartFrame();
    virtual float EndFrame();
    virtual RndAnimatable* AnimTarget();
    virtual void SetKey(float); // StubVoid

    // symbol from GDRB: ListAnimChildren__13RndAnimatableCFRQ211stlpmtx_std70list<P13RndAnimatable,Q211stlpmtx_std30StlNodeAlloc<P13RndAnimatable>>
    virtual void ListAnimChildren();

    static Symbol StaticClassName();

    ObjPtr<RndAnimatable, ObjectDir> animPtr;
    float period;
    float start;
    float end;
    float scale;
    float offset;
    float snap;
    float jitter;
    float unk38;
    int type;
};

#endif
