#ifndef RND_RNDANIMFILTER_HPP
#define RND_RNDANIMFILTER_HPP
#include "hmx/object.hpp"
#include "rndanimatable.hpp"
#include "objptr.hpp"

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
    // virtual void Loop(); // StubZero
    // virtual void StartAnim(); // StubVoid
    // virtual void EndAnim(); // StubVoid
    // virtual void SetFrame(float, float);
    // virtual float StartFrame(); // StubZerof
    // virtual float EndFrame(); // StubZerof
    // virtual RndAnimatable* AnimTarget();
    // virtual void SetKey(float); // StubVoid

    // // symbol from GDRB: ListAnimChildren__13RndAnimatableCFRQ211stlpmtx_std70list<P13RndAnimatable,Q211stlpmtx_std30StlNodeAlloc<P13RndAnimatable>>
    // virtual void ListAnimChildren(); // StubVoid

    static Symbol StaticClassName();

    ObjPtr<RndAnimatable, ObjectDir> ptr;
    float unk1c, unk20, unk24, unk28, unk2c, unk30, unk34, unk38;
    int unk3c;
};

#endif
