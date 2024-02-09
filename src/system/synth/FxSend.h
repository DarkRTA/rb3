#ifndef SYNTH_FXSEND_H
#define SYNTH_FXSEND_H
#include "hmx/object.hpp"
#include "objownerptr.hpp"

class FxSend : public Hmx::Object {
public:
    FxSend();
    virtual ~FxSend();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    virtual Symbol ClassName() const;
    virtual void SetType(Symbol);
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, Hmx::Object::CopyType);
    virtual void Load(BinStream&);

    static Symbol StaticClassName();

    ObjOwnerPtr<FxSend, ObjectDir> ptr;
    int unk28;
    char unk2c;
    float unk30, unk34, unk38, unk3c;
    char unk40, unk41;
    int unk44;
};

#endif
