#ifndef UI_PANELDIR_H
#define UI_PANELDIR_H
#include "rndobj/Dir.h"

class PanelDir : public RndDir {
public:
    PanelDir();
    virtual ~PanelDir();
    virtual void Replace(Hmx::Object*, Hmx::Object*);
    OBJ_CLASSNAME(PanelDir)
    OBJ_SET_TYPE(PanelDir)
    virtual DataNode Handle(DataArray*, bool);
    virtual bool SyncProperty(DataNode&, DataArray*, int, PropOp);
    virtual void Save(BinStream&);
    virtual void Copy(const Hmx::Object*, CopyType);
    virtual void PreLoad(BinStream&);
    virtual void PostLoad(BinStream&);
    virtual void SyncObjects();
    virtual void RemovingObject(Hmx::Object*);

    int filler;
};

#endif
