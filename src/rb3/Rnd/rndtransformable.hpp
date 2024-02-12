#ifndef RND_RNDTRANSFORMABLE_HPP
#define RND_RNDTRANSFORMABLE_HPP
#include "obj/ObjPtr_p.h"
#include "Rnd/rndhighlightable.hpp"

class RndTransformable : public RndHighlightable {
public:
    RndTransformable();
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);
    virtual ~RndTransformable();
    virtual void Replace(Hmx::Object *, Hmx::Object *);
    virtual void Highlight();
    virtual void Print();
    virtual void UpdatedWorldXfm(); // links to fn_8076F540_stub, which returns void

    Symbol StaticClassName();

    ObjPtr<RndTransformable, ObjectDir> rndTransOwnerPtr; // should actually be ObjOwnerPtr
    char vec[8]; // vector
    char transform1[0x30]; // some transform
    char transform2[0x30]; // some other transform
    int unk7c;
    short unk80;
    char unk82;
    ObjPtr<RndTransformable, ObjectDir> rndTransPtr;
};

#endif
